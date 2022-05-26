//
// Created by youpaw on 5/23/22.
//

#ifndef BLOCKREADER_HPP
#define BLOCKREADER_HPP

#include "DataBlock.hpp"
#include <memory>

class BlockReader{
	int _fd = -1;
	size_t _file_size;

	void *_file_map = nullptr;
	size_t _offset = 0;

	size_t _block_size;
	size_t _block_cnt = 0;

	void _map_file(char *file_path);

public:
	BlockReader(char *file_path, size_t block_size);

	std::shared_ptr<DataBlock> read();
	size_t count_blocks() const;

	~BlockReader();

};

#endif //BLOCKREADER_HPP
