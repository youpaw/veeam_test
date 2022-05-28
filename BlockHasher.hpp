//
// Created by youpaw on 5/23/22.
//

#ifndef BLOCKHASHER_HPP
#define BLOCKHASHER_HPP

#include "DataBlock.hpp"
#include <memory>
#include <boost/uuid/detail/md5.hpp>

using boost::uuids::detail::md5;

class BlockHasher{
	size_t _block_size;
	size_t _n_blocks;

	char *_hash_sum;
	const size_t _hash_size = sizeof(md5::digest_type);
	size_t _sum_size;

public:
    BlockHasher(size_t block_size, size_t n_blocks);

	void hash_md5(const DataBlock &block);

	~BlockHasher();
};

#endif //BLOCKHASHER_HPP
