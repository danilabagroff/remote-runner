/**
 @file CensoredBuffer.cpp
 @date 10.03.15

 @author Daniil A Megrabyan
 */

#include "CensoredBuffer.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace Net {
	const unsigned short CensoredBuffer::Fuse = 4048;
	const unsigned short CensoredBuffer::Batch = 1024;

	CensoredBuffer::CensoredBuffer(const std::string watermark)
	:
		_watermark(watermark)
	{
		_vector.resize(CensoredBuffer::Batch, 0);
		setg(_vector.data(), _vector.data(), _vector.data() + _vector.size());
		setp(_vector.data(), _vector.data() + _vector.size());
	}
	
	std::streamsize CensoredBuffer::xsputn(const char_type* sequence, std::streamsize count)
	{
		// Если получили все требуемые данные, то не принимаем новые данные
		if (_complete) {
			return 0;
		}
		
		// Увеличиваем буфер
		if ((epptr() - pbase()) < count) {
			// Защита от дурака/взлома — защита от веченого ожидания вотермарки
			if (_vector.size() + CensoredBuffer::Batch >= CensoredBuffer::Fuse) {
				// _complete = true;
				return 0;
			}
			
			// Увеличиваем буфер для принятия очередной пачки данных
			_vector.resize(_vector.size() + CensoredBuffer::Batch, 0);
		}
		
		// Длина
		std::streamsize length_before = (pptr() - pbase());
		
		// Поглощаем новые данные
		std::size_t retval = AbstractBuffer::xsputn(sequence, count);

		//  Ищем вотермарк
		std::vector<std::streambuf::char_type>::iterator i(std::search(_vector.begin(), _vector.end(), _watermark.begin(), _watermark.end()));

		// Нашли вотермарк!
		if (_vector.end() != i) {
			
			// Вычисляем полезные данные
			retval = (std::distance(_vector.begin(), i) + _watermark.length()) - length_before;
			
			/// @note Раньше было так, но это очень странный подход. Оставил на всякий случай.
			// Определяем размер лишнего *** и "отказываемся" от него как от принятого в буффер ***
			// retval -= (length - std::distance(_vector.begin(), i)) - _watermark.length();
			
			// Отсекаем лишнее
			resize(std::distance(_vector.begin(), i) + _watermark.length());
			
			// Устанавливаем признак завершенности буфера
			_complete = true;
		}
		
		return retval;
	}
} } } }
