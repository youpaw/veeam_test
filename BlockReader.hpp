//
// Created by youpaw on 5/23/22.
//

#ifndef BLOCKREADER_HPP
#define BLOCKREADER_HPP

#include "DataBlock.hpp"
#include <memory>
#include <fstream>

class BlockReader{
	std::ifstream _input;
	size_t _file_size;

	size_t _block_size;
	size_t _block_cnt = 0;

	void _allocate_block(DataBlock &block) const;

public:
	size_t n_blocks;

	BlockReader(std::string &file_path, size_t block_size);

	int read(DataBlock &block);
	size_t count_blocks() const;

	~BlockReader();

};

#endif //BLOCKREADER_HPP
