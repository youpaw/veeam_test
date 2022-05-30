//
// Created by youpaw on 5/25/22.
//
#include "ProduceConsumePipe.hpp"

ProduceConsumePipe::ProduceConsumePipe(std::shared_ptr<BlockReader> &producer,
										  std::shared_ptr<BlockHasher> &consumer) : _producer(producer),
										  											_consumer(consumer)
{
	_queue = std::move(std::queue<DataBlock>());
}

void ProduceConsumePipe::produce()
{
	DataBlock item;
	while (_producer->read(item))
	{
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
		_consumer->hash_sha256(item);
	}
}

void ProduceConsumePipe::async_consume(std::atomic<bool> &produce_complete)
{
	while (!produce_complete)
		consume();
	consume();
}
