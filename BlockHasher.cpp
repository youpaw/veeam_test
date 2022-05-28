//
// Created by youpaw on 5/23/22.
//

#include "BlockHasher.hpp"
#include <stdexcept>
#include <boost/algorithm/hex.hpp>

BlockHasher::BlockHasher(size_t block_size, size_t n_blocks) : _block_size(block_size), _n_blocks(n_blocks)
{
	_sum_size = _n_blocks * _hash_size;
	try
	{
		_hash_sum = new char[_sum_size];
	}
	catch (...)
	{
		std::throw_with_nested(std::runtime_error("Hash sum allocation failed"));
	}
}

void BlockHasher::hash_md5(const DataBlock &block)
{
	md5 hash;
	md5::digest_type digest;
	hash.process_bytes(block.data, _block_size);
	hash.get_digest(digest);

	const auto char_digest = reinterpret_cast<const char *>(&digest);
	char *result_addr = _hash_sum + block.cnt * _hash_size;
	boost::algorithm::hex(char_digest, char_digest + _hash_size, result_addr);
}

BlockHasher::~BlockHasher()
{
	delete [] _hash_sum;
}
