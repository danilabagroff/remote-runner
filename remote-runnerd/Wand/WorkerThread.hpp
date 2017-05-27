/**
 @file WorkerThread.hpp
 @date 02.04.15

 @author Daniil A Megrabyan
*/

#ifndef Wand_WorkerThread_hpp
#define Wand_WorkerThread_hpp

#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <memory>

#include "SharedQueue.hpp"

namespace wand {
	class worker_thread
	{
	/** @name Constructors */
	/** @{ */
	protected:
		worker_thread(bool done = false);
		worker_thread(const worker_thread&) = delete;
		worker_thread& operator=(const worker_thread&) = delete;
		
	public:
		virtual ~worker_thread();
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
		/// @brief Factory: safe construction & thread start
		static std::shared_ptr<worker_thread> instance();
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		/// @brief the queue w/ internal synchronization
		wand::shared_queue<std::function<void()>> _queue;
		std::thread _thread;
		/// @brief finished flag to be set through msg queue by ~worker_thread
		std::atomic<bool> _done;
	protected:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	private:
		void run();
		
	public:
		virtual void send(std::function<void()> msg);

	private:
		void done();
	/** @} */
	};
	
	class dummy_thread : public worker_thread
	{
	/** @name Constructors */
	/** @{ */
	private:
		dummy_thread();
		dummy_thread(const dummy_thread&) = delete;
		dummy_thread& operator=(const dummy_thread&) = delete;
		
	public:
		virtual ~dummy_thread();
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
		/// @brief Factory: safe construction & thread start
		static std::shared_ptr<dummy_thread> instance();
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual void send(std::function<void()> msg) override;
	/** @} */
	};
}

#endif
