//
// Created by youpaw on 5/23/22.
//

#ifndef BLOCKWRITER_HPP
#define BLOCKWRITER_HPP

#include "DataBlock.hpp"
#include <memory>
#include <boost/uuid/detail/md5.hpp>

using boost::uuids::detail::md5;

class BlockWriter{
    int _fd;
    size_t _file_size;

    void *_file_map;
    size_t _n_blocks;

    const size_t _hash_size = sizeof(md5::digest_type);

	void _map_file(char *file_path);

public:
    BlockWriter(char *file_path, size_t n_blocks);

	void write(const DataBlock &block);

	~BlockWriter();
};

#endif //BLOCKWRITER_HPP
