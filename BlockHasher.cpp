//
// Created by youpaw on 5/23/22.
//

#include "BlockHasher.hpp"
#include <stdexcept>

BlockHasher::BlockHasher(size_t block_size, size_t n_blocks) : _n_blocks(n_blocks), sum_size(_n_blocks * _hash_size)
{
	if (block_size)
		_block_size = block_size;
	try
	{
		_hash_sum = std::unique_ptr<char[]>(new char[sum_size]);
	}
	catch (...)
	{
		perror("Hash sum allocation failed");
		exit(errno);
	}
}

void BlockHasher::bytes_to_hex(const unsigned char *bytes, size_t size, char *dest)
{
	static const char hex_chars[] = {"0123456789abcdef"};

	for( auto i = 0; i < size; ++i )
	{
		dest[0] = hex_chars[ ( bytes[i] & 0xF0 ) >> 4 ];
		dest[1] = hex_chars[ ( bytes[i] & 0x0F ) >> 0 ];
		dest += 2;
	}
}

void BlockHasher::hash_sha1(const DataBlock &block)
{
	unsigned char digest[SHA_DIGEST_LENGTH];
	SHA1(reinterpret_cast<const unsigned char *>(block.data.get()), _block_size, digest);
	auto result = _hash_sum.get() + block.cnt * _hash_size;
	bytes_to_hex(digest, SHA_DIGEST_LENGTH, result);
}

const char *BlockHasher::get_sum()
{
	return _hash_sum.get();
}



