//
// Created by youpaw on 5/23/22.
//

#include "BlockReader.hpp"
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>

void BlockReader::_map_file(char *file_path)
{


	_fd = open(file_path, O_RDONLY);
	if (_fd < 0)
		throw std::runtime_error(strerror(errno));
	_file_map = mmap(NULL, _file_size, PROT_READ, MAP_SHARED, _fd, _file_size);
}

BlockReader::BlockReader(char *file_path, size_t block_size) : _block_size(block_size)
{
	struct stat st{};
	if 	(stat(file_path, &st))
		throw std::runtime_error(strerror(errno));
	_map_file(file_path);
}

size_t BlockReader::count_blocks() const
{
	size_t cnt = _file_size / _block_size;
	if (_file_size % _block_size != 0)
		cnt++;
	return cnt;
}

std::shared_ptr<DataBlock> BlockReader::read()
{
	if (_offset == _file_size)
		return nullptr;
	void *addr = (char *)_file_map + _offset;
	size_t remain = _file_size - _offset;
	size_t size = _block_size;
	if (remain < _block_size)
	{
		_offset += remain;
		size = remain;
	}
	else
		_offset += _block_size;
	return std::make_shared<DataBlock>(addr, size, _block_cnt++);
}

BlockReader::~BlockReader()
{
	if (_file_map)
		munmap(_file_map, _file_size);
	if (_fd >= 0)
		close(_fd);
}


