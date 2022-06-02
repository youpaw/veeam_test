//
// Created by youpaw on 5/26/22.
//

#include "DataBlock.hpp"

DataBlock::DataBlock() = default;

DataBlock::DataBlock(size_t block_size, size_t cnt) : cnt(cnt), data(std::unique_ptr<char[]>(new char[block_size]))
{}
