/**
 @file Configuration.cpp
 @date 11.06.15

 @author Daniil A Megrabyan
*/

#include "Configuration.hpp"

namespace DrWeb { namespace RemoteRunner {
	Configuration::Configuration(std::fstream& stream)
	:
		_stream(stream)
	{
		
	}
	
	Configuration::~Configuration()
	{

	}
	
	bool Configuration::open(const std::string filename)
	{
		if (isOpened()) {
			return false;
		}
		
		_stream.open(filename, std::ios_base::in);
		
		return isOpened();
	}

	bool Configuration::save()
	{
		return false;
	}
	
	bool Configuration::close()
	{
		if (isOpened()) {
			_stream.close();
			return isOpened();
		}
		
		return true;
	}
	
	bool Configuration::load(Core::System::AbstractPreference& preference)
	{
		if (!isOpened()) {
			return false;
		}
		
		/// @note В начало файла
		_stream.clear();
		_stream.seekg(std::ios_base::seekdir::beg);
		
		/// @note Фигачим до [section]
		std::string line;
		while (!std::getline(_stream, line).eof()) {
			if (line.compare(0, preference.getSectionName().size() + 2, "[" + preference.getSectionName() + "]") == 0) {
				break;
			}
		}
		
		/// @note Не нашли заданную секцию в файле
		if (_stream.eof()) {
			return false;
		}

		Core::System::AbstractPreference::OptionMap::const_iterator option(preference.cend());
		std::string key;
		while (_stream >> key) {
			if (_stream.fail()) {
				return false;
			}
			
			/// Пропустить комментарии
			if (key[0] == '#') {
				continue;
			}
			
			/// Прервать следующий блок
			if (key[0] == '[') {
				return true;
			}
			
			option = preference.find(key);
			if (preference.cend() != option) {
				if (!option->second(_stream)) {
					return false;
				}
			} else {
				/// @xxx return false;
			}
		}

		return true;
	}

	bool Configuration::validate(const Core::System::AbstractPreference& preference)
	{
		if (!isOpened()) {
			return false;
		}
		
		return true;
	}
	
	const bool Configuration::isOpened() const
	{
		return _stream.is_open();
	}
} }
