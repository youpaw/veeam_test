#include "ArgParser.hpp"
#include "BlockReader.hpp"
#include "BlockHasher.hpp"
#include "FileWriter.hpp"
#include "ProduceConsumePipe.hpp"
#include <atomic>
#include <thread>
#include <vector>

int main(int ac, char **av) {
	ArgParser args(ac, av);

	auto reader = std::make_shared<BlockReader>(args.input_file, args.block_size);
	FileWriter writer(args.output_file);
	auto hasher = std::make_shared<BlockHasher>(args.block_size, reader->n_blocks);

	ProduceConsumePipe pc_pipe(reader, hasher);
	std::atomic<bool> produce_complete = false;

	auto producer_func = [&pc_pipe](){pc_pipe.produce();};
	auto consumer_func = [&pc_pipe, &produce_complete](){pc_pipe.async_consume(produce_complete);};

	auto produce_thread = std::thread(producer_func);

	unsigned n_consume_threads = std::thread::hardware_concurrency() - 2;
	std::vector<std::thread> consume_threads;
	for (auto i = 0; i != n_consume_threads; ++i)
		consume_threads.emplace_back(std::thread(consumer_func));

	produce_thread.join();
	produce_complete = true;
	consume_threads.emplace_back(std::thread(consumer_func));
	n_consume_threads++;

	for(auto i = 0; i != n_consume_threads; ++i)
		consume_threads.at(i).join();

	writer.write(hasher->get_sum(), hasher->sum_size);
	return errno;
}
