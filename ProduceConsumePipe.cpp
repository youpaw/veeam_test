//
// Created by youpaw on 5/25/22.
//
#include "ProduceConsumePipe.hpp"

template<class T>
ProduceConsumePipe<T>::ProduceConsumePipe(size_t queue_size)
{
	_queue(queue_size);
}

template<class T>
void ProduceConsumePipe<T>::produce(std::shared_ptr<T> (*handler)(void))
{
	while (auto item = handler)
		while (!_queue->push(item))
			;
}

template<class T>
void ProduceConsumePipe<T>::consume(void (*handler)(T &))
{
	while(auto item = _queue->pop())
		handler(*item);
}

template<class T>
void ProduceConsumePipe<T>::async_consume(void (*handler)(std::shared_ptr<T>), boost::atomic<bool> produce_complete)
{
	while (!produce_complete)
		consume(handler);
	consume(handler);
}
