//
// Created by youpaw on 5/26/22.
//

#include <iostream>
#include "DataBlock.hpp"

DataBlock::DataBlock() : data(nullptr), cnt(0)
{}

DataBlock::DataBlock(char *data, size_t cnt) : data(data), cnt(cnt)
{}

DataBlock::~DataBlock()
{
//	std::cout << "Destruct DataBlock";
	delete [] data;
	data = nullptr;
}
