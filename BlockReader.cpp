//
// Created by youpaw on 5/23/22.
//

#include "BlockReader.hpp"
#include <thread>
#include <exception>
#include <cstring>
#include <filesystem>

BlockReader::BlockReader(std::string &file_path, size_t block_size) : _block_size(block_size)
{
	_input = std::ifstream(file_path, std::ios::in | std::ios::binary);
	if (!_input)
	{
		perror(file_path.c_str());
		throw std::runtime_error("Cannot open source file for reading");
	}
	if (!std::filesystem::is_regular_file(file_path))
		throw std::runtime_error("Provided source path is not a file");
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

void BlockReader::_allocate_block(DataBlock &block) const
{
	unsigned timeout = 1;
	unsigned step = 5;
	while (true)
	{
		try
		{
			block = DataBlock(_block_size, _block_cnt);
			return ;
		}
		catch(...)
		{
			if (timeout > 10000)
			{
				perror(nullptr);
				std::throw_with_nested(std::runtime_error("Block allocation failed"));
			}
			std::this_thread::sleep_for(std::chrono::microseconds(timeout) );
			timeout += step;
			step *= 2;
		}
	}
}

int BlockReader::read(DataBlock &block)
{
	if (_block_cnt == n_blocks)
		return 0;
	_allocate_block(block);
	const auto data = block.data.get();
	_input.read(data, _block_size);
	if (!_input)
	{
		auto n_bytes = _input.gcount();
		bzero(data + n_bytes, _block_size - n_bytes);
	}
	_block_cnt++;
	return 1;
}

BlockReader::~BlockReader()
{
	_input.close();
};


