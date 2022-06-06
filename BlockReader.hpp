//
// Created by youpaw on 5/23/22.
//

#ifndef BLOCKREADER_HPP
#define BLOCKREADER_HPP

#include "DataBlock.hpp"
#include "main.hpp"
#include <memory>
#include <fstream>

class BlockReader{
	std::ifstream _input{};
	size_t _file_size = 0;

	size_t _block_size = MEGABYTE;
	size_t _block_cnt = 0;

public:
	size_t n_blocks = 0;

	BlockReader(std::string &file_path, size_t block_size);

	DataBlock read();
	bool next() const;
	size_t count_blocks() const;

	~BlockReader();

};

#endif //BLOCKREADER_HPP
