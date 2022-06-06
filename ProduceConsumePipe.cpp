//
// Created by youpaw on 5/25/22.
//
#include "ProduceConsumePipe.hpp"
#include <thread>

ProduceConsumePipe::ProduceConsumePipe(std::shared_ptr<BlockReader> &producer,
										  std::shared_ptr<BlockHasher> &consumer) : _producer(producer),
										  											_consumer(consumer),
																				  	_queue(std::queue<DataBlock>())
{}

void ProduceConsumePipe::produce()
{
	unsigned timeout = 25;
	DataBlock item;
	while (_producer->next())
	{
		try
		{
			item = _producer->read();
		}
		catch (...)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(timeout));
			continue;
		}
		_sync.lock();
		_queue.push(std::move(item));
		_sync.unlock();
	}
}

void ProduceConsumePipe::consume()
{
	while(true)
	{
		_sync.lock();
		if (_queue.empty())
		{
			_sync.unlock();
			return;
		}
		auto item = std::move(_queue.front());
		_queue.pop();
		_sync.unlock();
		_consumer->hash_sha1(item);
	}
}

void ProduceConsumePipe::async_consume(std::atomic<bool> &produce_complete)
{
	unsigned timeout = 50;
	while (!produce_complete)
	{
		consume();
		std::this_thread::sleep_for(std::chrono::microseconds(timeout));
	}
	consume();
}
