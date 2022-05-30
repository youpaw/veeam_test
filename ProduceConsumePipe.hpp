//
// Created by youpaw on 5/24/22.
//

#ifndef PRODUCECONSUMEPIPE_HPP
#define PRODUCECONSUMEPIPE_HPP

#include "BlockReader.hpp"
#include "BlockHasher.hpp"
#include "DataBlock.hpp"
#include <cstddef>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>

class ProduceConsumePipe{
	std::shared_ptr<BlockReader> _producer;
	std::shared_ptr<BlockHasher> _consumer;
	std::queue<DataBlock> _queue;
	std::mutex _sync;
public:

	ProduceConsumePipe(std::shared_ptr<BlockReader> &producer, std::shared_ptr<BlockHasher> &consumer);
	void produce();
	void consume();
	void async_consume(std::atomic<bool> &produce_complete);
};

#endif //PRODUCECONSUMEPIPE_HPP
