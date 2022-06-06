//
// Created by youpaw on 5/23/22.
//

#include "BlockReader.hpp"
#include <cstring>
#include <filesystem>

BlockReader::BlockReader(std::string &file_path, size_t block_size) :
_input(std::ifstream(file_path, std::ios::in | std::ios::binary))
{
	if (block_size)
		_block_size = block_size;
	if (!_input)
	{
		perror("Cannot open source file for reading");
		exit(errno);
	}
	if (!std::filesystem::is_regular_file(file_path))
	{
		perror("Provided source path is not a file");
		exit(EINVAL);
	}
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

bool BlockReader::next() const
{
	return _block_cnt < n_blocks;
}

DataBlock BlockReader::read()
{
	auto block = DataBlock(_block_size, _block_cnt);
	const auto data = block.data.get();
	_input.read(data, _block_size);
	if (!_input)
	{
		auto n_bytes = _input.gcount();
		bzero(data + n_bytes, _block_size - n_bytes);
	}
	_block_cnt++;
	return block;
}

BlockReader::~BlockReader()
{
	_input.close();
}
