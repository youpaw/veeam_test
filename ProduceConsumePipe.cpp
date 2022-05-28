//
// Created by youpaw on 5/25/22.
//
#include "ProduceConsumePipe.hpp"

ProduceConsumePipe::ProduceConsumePipe(BlockReader *producer, BlockHasher *consumer) :
		_producer(producer), _consumer(consumer)
{}

void ProduceConsumePipe::produce()
{
	while (auto item = _producer->read())
	{
		_queue.push_back(std::move(item));
	}
}

void ProduceConsumePipe::consume()
{
	while(!_queue.empty())
	{
		auto item = std::move(_queue.front());
		_queue.pop_front();
		_consumer->hash_md5(*item);
	}
}

void ProduceConsumePipe::async_consume(boost::atomic<bool> produce_complete)
{
	while (!produce_complete)
		consume();
	consume();
}
