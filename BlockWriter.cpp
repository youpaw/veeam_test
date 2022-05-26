//
// Created by youpaw on 5/23/22.
//

#include "BlockWriter.hpp"
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>


void BlockWriter::_map_file(char *file_path)
{
	_fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC);
	if (_fd < 0)
		throw std::runtime_error(strerror(errno));
	_file_map = mmap(NULL, _file_size, PROT_WRITE, MAP_SHARED, _fd, _file_size);
}

BlockWriter::BlockWriter(char *file_path, size_t n_blocks) : _n_blocks(n_blocks)
{
	_file_size = _hash_size * _n_blocks;
	_map_file(file_path);
}

void BlockWriter::write(const DataBlock &block)
{

	md5 hash;
	md5::digest_type digest;
	void *hash_addr = (char *)_file_map + block.cnt * _hash_size;

	hash.process_bytes(block.addr, block.size);
	hash.get_digest(digest);
	memmove(hash_addr, digest, _hash_size);
}

BlockWriter::~BlockWriter()
{
	if (_file_map)
		munmap(_file_map, _file_size);
	if (_fd >= 0)
		close(_fd);
}
