/**
 @file HashTable.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef Wand_HashTable_hpp
#define Wand_HashTable_hpp

#include <list>
#include <unordered_map>
#include <memory>

#include "Hash.hpp"

namespace wand {
	template <typename TValue>
	class hash_table
	{
	/** @name Aliases */
	/** @{ */
	public:
		using table_type = typename std::unordered_map<std::size_t, std::shared_ptr<TValue>>;
		using list_type = typename std::list<typename table_type::const_iterator>;
		
		using iterator = typename list_type::iterator;
		using const_iterator = typename list_type::const_iterator;
		using value_type = typename list_type::value_type;
	/** @} */

	/** @name Constructors */
	/** @{ */
	public:
		hash_table<TValue>() = default;
		hash_table<TValue>(const std::size_t length)
		:
			_map(length)
		{

		}
		virtual ~hash_table() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		table_type _map;
		list_type _list;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		std::shared_ptr<TValue> get(const std::size_t id) const
		{
			typename table_type::const_iterator i(_map.find(id));
			if (i == _map.end()) {
				return nullptr;
			}
			
			return i->second;
		}

		const_iterator begin() const
		{
			return _list.begin();
		}
		
		const_iterator end() const
		{
			return _list.end();
		}

		const_iterator find(const std::size_t id) const
		{
			return _list.find(_map.find(id));
		}

		const_iterator find(const std::shared_ptr<TValue> value) const
		{
			return find_if(_list.begin(), _list.end(), [&value](typename list_type::value_type const& i) { return (*i).second == value; });
		}
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
		std::pair<const_iterator, bool> insert(std::shared_ptr<TValue> value)
		{
			if (nullptr == value) {
				return std::make_pair(_list.end(), false);
			}
			/// @xxx What if already exists?
			std::pair<typename table_type::const_iterator, bool> insertion(_map.insert(typename table_type::value_type(wand::hash<TValue>()(value), value)));
			
			return std::make_pair(_list.insert(_list.end(), insertion.first), insertion.second);
		}

		void clear()
		{
			_map.clear();
			_list.clear();
		}
		
		bool erase(const_iterator i)
		{
			_list.erase(i);
			_map.erase(i);

			/// @note Always succeeds (unless of course, it gets an invalid iterator, in which case the results are undefined)
			return true;
		}

		bool erase(const std::shared_ptr<TValue> value)
		{
			const_iterator i(find(value));
			if (_map.end() != *i) {
				_list.erase(i);
				_map.erase(*i);
				
				return true;
			}

			return false;
		}

		bool erase(const std::size_t id)
		{
			const_iterator i(find(id));
			
			if (_list.end() == i) {
				return false;
			}
			
			_list.erase(i);
			_map.erase((*i));
			
			return true;
		}
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		bool empty() const
		{
			return _map.size() <= 0 ? true : false;
		}
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
		std::shared_ptr<TValue> operator()(const std::size_t id)
		{
			return get(id);
		}
		
		std::shared_ptr<const TValue> operator()(const std::size_t id) const
		{
			return get(id);
		}
	/** @} */
	};
}
#endif
