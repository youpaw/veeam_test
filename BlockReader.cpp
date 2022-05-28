//
// Created by youpaw on 5/23/22.
//

#include "BlockReader.hpp"
#include <thread>
#include <exception>
#include <cstring>

BlockReader::BlockReader(std::string &file_path, size_t block_size) : _block_size(block_size)
{
	_input = std::ifstream(file_path, std::ios::in | std::ios::binary);
	_input.seekg(0, _input.end);
	_file_size = _input.tellg();
	_input.seekg(0, _input.beg);
	n_blocks = count_blocks();
}

size_t BlockReader::count_blocks() const
{
	if (_file_size == 0)
		return (0);
	else if (_file_size < _block_size)
		return (1);
	size_t cnt = _file_size / _block_size;
	if (_file_size % _block_size != 0)
		cnt++;
	return cnt;
}

char *BlockReader::_allocate_block() const
{
	char *data = nullptr;
	unsigned timeout = 1;
	unsigned step = 5;
	while (!data)
	{
		try
		{
			data = new char[_block_size];
		}
		catch(...)
		{
			if (timeout > 10000)
				std::throw_with_nested(std::runtime_error("Block allocation failed"));
			std::this_thread::sleep_for(std::chrono::microseconds(timeout) );
			timeout += step;
			step *= 2;
		}
	}
	return data;
}

std::unique_ptr<DataBlock> BlockReader::read()
{
	if (_block_cnt == n_blocks)
		return nullptr;
	auto data = _allocate_block();

	_input.read(data, _block_size);
	if (!_input)
	{
		auto n_bytes = _input.gcount();
		bzero(data + n_bytes, _block_size - n_bytes);
	}
//	auto data_block = DataBlock(data, _block_cnt++);
//	auto block = std::shared_ptr<DataBlock>(new DataBlock(data, _block_cnt++));
	return std::make_unique<DataBlock>(data, _block_cnt++);
}

BlockReader::~BlockReader()
{
	_input.close();
};


