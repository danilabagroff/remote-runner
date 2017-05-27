/**
 @file AsyncThen.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 @todo Закочить комментарии
*/

#ifndef Wand_AsyncThen_hpp
#define Wand_AsyncThen_hpp

#include <future>

namespace wand {
	/**
	 @brief Отложенное выполнение
	 @details Немного напоминает deffer
	 
	 @param f
	 @param l Функция для вызова
	 
	 @return 
	 */
	template <typename T, typename Lambda>
	auto then(std::future<T> f, Lambda l) -> std::future<decltype(l(f.get()))>
	{
		return std::async([]
						  (std::future<T> f, Lambda l)
						  {
							  return l(f.get());
						  },
						  std::move(f),
						  std::move(l)
		);
	}
	
	/**
	 @brief Отложенное выполнение
	 @details Немного напоминает deffer
	 
	 @param f
	 @param l Функция для вызова
	 
	 @return
	 */
	template <typename T, typename Lambda>
	auto then(std::shared_future<T> f, Lambda l) -> std::future<decltype(l(f.get()))>
	{
		return std::async([]
						  (std::shared_future<T> f, Lambda l)
						  {
							  return l(f.get());
						  },
						  f,
						  std::move(l)
		);
	}
}

#endif
