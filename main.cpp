#include "DataBlock.hpp"
#include "BlockReader.hpp"
#include "BlockWriter.hpp"
#include "ProduceConsumePipe.hpp"
#include <boost/atomic.hpp>
#include <boost/thread/thread.hpp>

int main(int ac, char **av) {
    if (ac != 3)
    {
        return EINVAL;
    }
	BlockReader reader(av[1], 1024);
	BlockWriter writer(av[2], reader.count_blocks());
	ProduceConsumePipe<DataBlock> pc_pipe(128);
	blf::queue<std::shared_ptr<int>> _queue;
}

