//
// Created by youpaw on 5/23/22.
//

#ifndef BLOCKHASHER_HPP
#define BLOCKHASHER_HPP

#include "DataBlock.hpp"
#include "main.hpp"
#include <memory>
#include <openssl/sha.h>

class BlockHasher{
	size_t _block_size = MEGABYTE;
	size_t _n_blocks = 0;

	std::unique_ptr<char[]> _hash_sum{};
	const size_t _hash_size = SHA_DIGEST_LENGTH * 2;

public:
	const size_t sum_size = 0;

	BlockHasher(size_t block_size, size_t n_blocks);
	static void bytes_to_hex(const unsigned char *bytes, size_t size, char *dest);
	void hash_sha1(const DataBlock &block);
	const char *get_sum();

};

#endif //BLOCKHASHER_HPP
