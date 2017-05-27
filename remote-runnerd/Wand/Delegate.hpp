/**
 @file Delegate.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 @todo Закончить с комментариями
*/

#ifndef Wand_Delegate_hpp
#define Wand_Delegate_hpp

#include <functional>
#include <list>

namespace wand {
	/**
	 @brief Делегат событий
	 @details Общая идея с Observer
	 */
	template<typename F>
	class delegate : public std::function<F>
	{
	/*
	using ResultType = std::list<typename std::function<F>::ResultType>;
	using AllocatorType = typename std::function<F>::AllocatorType;
	*/

	/** @name Properties */
	/** @{ */
	private:
		std::list<std::function<F>> _list;
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		explicit delegate()
		{
		
		}
		
		/**
		 @brief The implicitly generated copy constructor, copy assignment, and destructor are fine.
		 @param f
		 @return
		 */
		template<typename F2>
		delegate(std::function<F2> f)
		{
			_list.push_back(f);
		}
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
		/**
		 @brief If you have an implementation of function that supports. Equality comparison, uncomment the calls to remove.
		 @param f
		 @return
		 */
		void add(std::function<F> f)
		{
			//_list.remove(f);
			_list.push_back(f);
		}

		void remove(std::function<F> f)
		{
			//_list.remove(f);
		}

		void swap(delegate& other)
		{
			_list.swap(other._list);
		}

		void clear()
		{
			_list.clear();
		}
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
		void operator+=(std::function<F> f)
		{
			add(f);
		}
		
		void operator-=(std::function<F> f)
		{
			remove(f);
		}

		template<typename... Ts>
		void operator()(Ts... vs) const
		{
			for (auto i=begin(_list); i!=end(_list); ++i) {
				(*i)(vs...);
			}
		}
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		bool empty() const
		{
			return _list.empty();
		}
		
		operator bool() const
		{
			return _list.empty();
		}
	/** @} */
	};

	template<typename MF1, typename MF2>
	void swap(delegate<MF1>& mf1, delegate<MF2>& mf2)
	{
		mf1.swap(mf2);
	}

	template<typename MF1, typename MF2>
	bool operator==(const delegate<MF1>& mf1, const delegate<MF2>& mf2)
	{
		return false;
	}
		
	template<typename MF1, typename MF2>
	bool operator!=(const delegate<MF1>& mf1, const delegate<MF2>& mf2)
	{
		return !(mf1 == mf2);
	}
}
#endif
