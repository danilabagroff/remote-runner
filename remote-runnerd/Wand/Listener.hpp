/**
 @file Listener.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
 @todo Закончить документирование
*/

#ifndef Wand_Listener_hpp
#define Wand_Listener_hpp

#include "Delegate.hpp"
#include "Type.hpp"
#include "Hash.hpp"

#include <tuple>

namespace wand {
	template<typename...>
	class listener;
	
	template<typename TEvent>
	class listener<TEvent>
	{
	/** @name Constructors */
	/** @{ */
	public:
		virtual ~listener() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		wand::delegate<bool(const TEvent&)> _congress;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual void add(std::function<bool(const TEvent&)> delegate)
		{
			_congress.add(delegate);
		};
		
	public:
		template<typename TStream>
		bool dispatch(TStream& stream)
		{
			std::uint16_t type(stream.readType());
			
			TEvent e;
			
			if (e == type) {
				e.apply(stream);
				on(e);

				return true;
			}
			
			return false;
		};
		
		template<typename TStream>
		bool dispatch(TStream& stream, const TEvent&)
		{
			TEvent e;
			e.apply(stream);
			on(e);
			   
			return true;
		};
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		bool has(const TEvent&) const
		{
			return !_congress.empty();
		};
	/** @} */
		
	/** @name Hooks */
	/** @{ */
	public:
		void on(const TEvent& event)
		{
			_congress(event);
		};
	/** @} */
	};

	template<typename TEvent, typename... TEvents>
	class listener<TEvent, TEvents...> : public listener<TEvent>, listener<TEvents...>
	{
	/** @name Aliases */
	/** @{ */
	public:
		using listener<TEvent>::add;
		using listener<TEvents...>::add;
		using listener<TEvent>::on;
		using listener<TEvents...>::on;
		using listener<TEvent>::dispatch;
		using listener<TEvents...>::dispatch;
	/** @} */
	/** @name Constructors */
	/** @{ */
	public:
		listener()
		:
			listener<TEvents...>(),
			_tuple(TEvent{}, TEvents{}...)
		{
			
		}
		
		virtual ~listener() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::tuple<const TEvent, const TEvents...> _tuple;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	protected:
		template<std::size_t I = 0, typename... Tp, typename TStream>
		inline typename std::enable_if<I == sizeof...(Tp), bool>::type
		dispatch(std::tuple<Tp...>& t, TStream& stream, const std::uint16_t type)
		{
			return false;
		}
		
		template<std::size_t I = 0, typename... Tp, typename TStream>
		inline typename std::enable_if<I<sizeof...(Tp), bool>::type
		dispatch(std::tuple<Tp...>& t, TStream& stream, const std::uint16_t type)
		{
			if (std::get<I>(t) == type) {
				//typename std::remove_reference<decltype(std::get<I>(t))>::type event;
				auto event(std::get<I>(t));			
				return dispatch(stream, event);
			} else {
				return dispatch<I + 1, Tp...>(t, stream, type);
			}
		}
		
	public:
		template<typename TStream>
		bool dispatch(TStream& stream)
		{
			const std::uint16_t type(stream.readType());
			return dispatch(_tuple, stream, type);
		}
	/** @} */
	};
		
	template<>
	class listener<>
	{
	/** @name Procedures  */
	/** @{ */
	public:
		template<typename TStream>
		bool dispatch(TStream& stream)
		{
			return false;
		}
	/** @} */		
	};
		
	template<typename TEvent1, typename TEvent2>
	bool operator==(const listener<TEvent1>& listener1, const listener<TEvent2>& listener2)
	{
		return false;
	}
		
	template<typename TEvent1, typename TEvent2>
	bool operator!=(const listener<TEvent1>& listener1, const listener<TEvent2>& listener2)
	{
		return !(listener1 == listener2);
	}
}
#endif
