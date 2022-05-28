//
// Created by youpaw on 5/26/22.
//

#ifndef DATABLOCK_HPP
#define DATABLOCK_HPP

#include <cstddef>
#include <memory>

struct DataBlock{
	char *data;
	size_t cnt;

	DataBlock();
	DataBlock(char *data, size_t cnt);
	~DataBlock();
};

#endif //DATABLOCK_HPP
