//
// Created by youpaw on 5/26/22.
//

#ifndef DATABLOCK_HPP
#define DATABLOCK_HPP

#include <cstddef>

struct DataBlock{
	void *addr;
	size_t size;
	size_t cnt;

	DataBlock();
	DataBlock(void *addr, size_t size, size_t cnt);
};

#endif //DATABLOCK_HPP
