/**
 @file Coroutine.hpp
 @date 14.03.16

 @author Daniil A Megrabyan
*/

#ifndef Wand_Coroutine_hpp
#define Wand_Coroutine_hpp

#include <atomic>
#include <memory>
#include <future>
#include <list>

namespace wand {
	template<typename T1, typename T2>
	class coroutine : public std::enable_shared_from_this<coroutine<T1, T2>>
	{
	/** @name Classes */
	/** @{ */
	public:
	/** @} */
		
	/** @name Aliases */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
	
	/** @name Constructors */
	/** @{ */
	public:
		coroutine(T1 dummy_value)
		:
			_idle(true)
		{
			std::promise<T1> dummy;
			_fuse = dummy.get_future();
			dummy.set_value(dummy_value);
		};
		
		virtual ~coroutine() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::atomic_bool _idle;
		
		/// @todo persistent flag
		std::list<std::shared_ptr<wand::coroutine<T1, T2>>> _dependancy_list;
		
		std::shared_future<T1> _fuse;
	protected:
	/** @} */

	/** @name Procedures  */
	/** @{ */
	public:
		virtual std::shared_future<T1> async(T2 argument) final
		{
			std::shared_future<T1> fuse(_fuse);
			
			/// @note VC++ 2010 does not implement the lookup rules for templated base classes exactly correctly. The clang behavior is correct. The above fix will make it work on both your platforms.
			
			return (_fuse = std::async(std::launch::async, &coroutine::then, this->shared_from_this(), fuse, argument));
		};
		
		virtual T1 sync(T2 argument) final
		{
			return co(argument);
		};
		
		virtual void wait()
		{
			_fuse.wait();
		};
		
	protected:
		virtual T1 co(T2 argument) = 0;
		
	private:
		virtual T1 then(std::shared_future<T1> fuse, T2 argument) final
		{
			fuse.wait();
			
			for (std::shared_ptr<coroutine> co : _dependancy_list) {
				co->wait();
			}
			
			_idle = false;
			
			T1 retval(co(argument));
			
			_idle = true;
			
			return retval;
		};
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
		virtual void depend(std::initializer_list<std::shared_ptr<coroutine<T1, T2>>> routine_list) final
		{
			for (std::shared_ptr<coroutine> co : routine_list) {
				_dependancy_list.push_back(co);
			}
		};
		
		virtual void depend(std::shared_ptr<coroutine> co) final
		{
			_dependancy_list.push_back(co);
		};
	/** @} */
	
	/** @name Getters */
	/** @{ */
	public:
		std::shared_future<T1> future()
		{
			return _fuse;
		};
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		const bool idle() const
		{
			return _idle;
		};
	/** @} */
	};
}

#endif
