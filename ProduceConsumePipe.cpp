//
// Created by youpaw on 5/25/22.
//
#include "ProduceConsumePipe.hpp"

ProduceConsumePipe::ProduceConsumePipe(BlockReader *producer, BlockHasher *consumer) :
		_producer(producer), _consumer(consumer)
{}

void ProduceConsumePipe::produce()
{
	DataBlock item;
	while (_producer->read(item))
	{
		_queue.push(item);
	}
}

void ProduceConsumePipe::consume()
{
	while(!_queue.empty())
	{
		auto item = _queue.front();
		_queue.pop();
		_consumer->hash_md5(item);
	}
}

void ProduceConsumePipe::async_consume(boost::atomic<bool> produce_complete)
{
	while (!produce_complete)
		consume();
	consume();
}
