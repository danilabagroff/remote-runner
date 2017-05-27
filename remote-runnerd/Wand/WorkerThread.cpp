/**
 @file WorkerThread.cpp
 @date 02.04.15

 @author Daniil A Megrabyan
*/

#include "WorkerThread.hpp"

namespace wand {
	std::shared_ptr<worker_thread> worker_thread::instance()
	{
		std::shared_ptr<worker_thread> instance(new worker_thread());
		instance->_thread = std::thread(&worker_thread::run, instance.get());
		
		return instance;
	}

	worker_thread::worker_thread(bool done)
	:
		_done(done)
	{

	}

	worker_thread::~worker_thread()
	{
		if (!_done) {
			std::function<void()> quit_token = std::bind(&worker_thread::done, this);
			send(quit_token);
		}
		if (_thread.joinable()) {
			_thread.join();
		}
	}

	void worker_thread::send(std::function<void()> msg)
	{
		_queue.push(msg);
	}

	void worker_thread::run()
	{
		while (!_done) {
			std::function<void()> f;
			_queue.wait_and_pop(f);
			f();
		}
	}
	
	void worker_thread::done()
	{
		_done = true;
	}
	
	std::shared_ptr<dummy_thread> dummy_thread::instance()
	{
		std::shared_ptr<dummy_thread> instance(new dummy_thread());
		
		return instance;
	}
	
	dummy_thread::dummy_thread()
	:
		worker_thread(true)
	{

	}
	
	dummy_thread::~dummy_thread()
	{
	
	}
	
	void dummy_thread::send(std::function<void()> msg)
	{
	
	}
}
