#include "BlockReader.hpp"
#include "BlockHasher.hpp"
#include "ProduceConsumePipe.hpp"
#include <boost/atomic.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <queue>

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
	return 0;
}
