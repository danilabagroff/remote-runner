/**
 @file SingletonPool.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef Wand_SingletonPool_hpp
#define Wand_SingletonPool_hpp

#include <memory>
#include <unordered_map>

namespace wand {
	/**
	 @brief Глобальный пул одиночек
	 */
	template<typename T>
	class singleton_pool
	{
	using singleton_pool_map = typename std::unordered_map<std::size_t, std::shared_ptr<T>>;

	/** @name Constructors */
	/** @{ */
	public:
		static singleton_pool<T>& Instance()
		{
			static singleton_pool<T> instance;
			
			return instance;
		}
		
	private:
		singleton_pool() = default;

	public:
		singleton_pool(const singleton_pool&) = delete;
		singleton_pool& operator=(const singleton_pool&) = delete;
		virtual ~singleton_pool() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::unordered_map<std::size_t, std::shared_ptr<T>> _map;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		std::shared_ptr<T> at(std::size_t hash) const
		{
			/// @todo: mutex
			typename singleton_pool_map::const_iterator i = _map.find(hash);
			
			return i != _map.end() ? i->second : nullptr;
		}
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
		std::shared_ptr<T> add(std::shared_ptr<T> t)
		{
			/// @todo: mutex
			_map.emplace(std::hash<std::shared_ptr<T>>()(t), t);
			
			return t;
		}

		bool remove(std::shared_ptr<T> t)
		{
			/// @todo: mutex
			typename singleton_pool_map::const_iterator i = std::find_if(_map.begin(), _map.end(), [&t](const typename singleton_pool_map::value_type& value) { return value.second == t; });
			
			return _map.erase(i) == i++ ? true : false;
		}

		bool remove(std::size_t hash)
		{
			/// @todo: mutex
			return _map.erase(hash) == 1 ? true : false;
		}
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
		std::shared_ptr<T> operator[](std::size_t hash) const
		{
			return at(hash);
		}
		
		void operator+=(std::shared_ptr<T> t)
		{
			add(t);
		}
		
		void operator-=(std::size_t hash)
		{
			remove(hash);
		}
		
		void operator-=(std::shared_ptr<T> t)
		{
			remove(t);
		}
	/** @} */
	};
}

#endif
