//
// Created by youpaw on 5/24/22.
//

#ifndef PRODUCECONSUMEPIPE_HPP
#define PRODUCECONSUMEPIPE_HPP

#include "DataBlock.hpp"
#include "BlockReader.hpp"
#include "BlockHasher.hpp"
#include <cstddef>
#include <list>
#include <mutex>
#include <boost/atomic.hpp>

class ProduceConsumePipe{
	std::mutex _sync;
	BlockReader *_producer;
	BlockHasher *_consumer;
	std::list<std::unique_ptr<DataBlock>> _queue;
public:

	explicit ProduceConsumePipe(BlockReader *producer, BlockHasher *consumer);
	void produce();
	void consume();
	void async_consume(boost::atomic<bool> produce_complete);
};


#endif //PRODUCECONSUMEPIPE_HPP
