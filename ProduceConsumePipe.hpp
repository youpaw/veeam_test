//
// Created by youpaw on 5/24/22.
//

#ifndef PRODUCECONSUMEPIPE_HPP
#define PRODUCECONSUMEPIPE_HPP

#include <cstddef>
#include <boost/atomic.hpp>
#include <boost/lockfree/queue.hpp>

namespace blf = boost::lockfree;

template <class T>
class ProduceConsumePipe{
	blf::queue<std::shared_ptr<T>> _queue;
public:
	explicit ProduceConsumePipe(size_t queue_size = 128);
	void produce(std::shared_ptr<T> (*handler)(void));
	void consume(void (*handler)(T &));
	void async_consume(void (*handler)(std::shared_ptr<T>), boost::atomic<bool> produce_complete);
};


#endif //PRODUCECONSUMEPIPE_HPP
