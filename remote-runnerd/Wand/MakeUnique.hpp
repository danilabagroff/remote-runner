/**
 @file MakeUnique.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef Wand_MakeUnique_hpp
#define Wand_MakeUnique_hpp

#include <future>

namespace wand {
	/**
	 @brief Недостающий аналог std::make_shared<>
	 @details Exception-safe метод создания умных указателей
	 
	 @param ...args Аргументы для конструктора
	 
	 @return Умный уникальный указатель
	 */
	template<typename T, typename ...Args>
	std::unique_ptr<T> make_unique(Args&& ...args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)... ));
	}
}

#endif
