//
// Created by youpaw on 5/26/22.
//

#include "DataBlock.hpp"

DataBlock::DataBlock() : addr(nullptr), size(0), cnt(0)
{}

DataBlock::DataBlock(void *addr, size_t size, size_t cnt) : addr(addr), size(size), cnt(cnt)
{}