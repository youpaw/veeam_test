#include "BlockReader.hpp"
#include "BlockHasher.hpp"
#include "ProduceConsumePipe.hpp"
#include <boost/atomic.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <queue>

std::shared_ptr<DataBlock> get()
{
	std::shared_ptr<DataBlock> sp(new DataBlock(new char[10], 0));
	return sp;
}

int main(int ac, char **av) {
    if (ac != 4)
    {
        return EINVAL;
    }
	auto input_file = std::string(av[1]);
	auto output_file = std::string(av[2]);
	size_t block_size = std::strtoull(av[3], nullptr, 10);
	BlockReader reader(input_file, block_size);
	BlockHasher hasher(block_size, reader.n_blocks);
	ProduceConsumePipe pc_pipe(&reader, &hasher);
	pc_pipe.produce();
	pc_pipe.consume();
//	std::queue<std::shared_ptr<DataBlock>> queue;
//	auto sp = get();
//	queue.push(sp);
//	sp = nullptr;
//	auto sp1 = queue.front();
//	queue.pop();
//	sp1 = nullptr;
	return 0;
}
