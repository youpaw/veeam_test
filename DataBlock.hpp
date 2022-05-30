//
// Created by youpaw on 5/26/22.
//

#ifndef DATABLOCK_HPP
#define DATABLOCK_HPP

#include <cstddef>
#include <memory>

struct DataBlock{
	std::unique_ptr<char[]> data;
	size_t cnt;

	DataBlock();
	DataBlock(size_t block_size, size_t cnt);
};

#endif //DATABLOCK_HPP
