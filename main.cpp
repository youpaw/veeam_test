#include <iostream>
#include <cerrno>
#include <sys/mman.h>
#include <sys/stat.h>
#include <libc.h>

struct DataBlock{
    void *block_addr;
    size_t block_size;
    void *hash_addr;

    DataBlock(void *block_addr, size_t block_size, void *hash_addr) : block_addr(block_addr), block_size(block_size),
    hash_addr(hash_addr)
    {}
};

class BlockProducer{
    int _fd;
    size_t _file_size;

    void *_file_map;
    size_t _offset;

    size_t _block_size;


public:
    BlockProducer(char *file_path, size_t block_size) : _block_size(block_size), _fd(-1), _file_map(nullptr)
    {
        map_file(file_path);
    }

    void map_file(char *file_path)
    {
        struct stat st;

        this->~BlockProducer();
        _fd = open(file_path, O_RDONLY);
        if (_fd < 0)
            throw std::runtime_error("Can't open file for reading");
        stat(file_path, &st);
        _file_size = st.st_size;
        _offset = 0;
        _file_map = mmap(NULL, _file_size, PROT_READ, MAP_SHARED, _fd, _file_size);
    }

    std::shared_ptr<DataBlock> produce_block()
    {
        if (_offset == _file_size)
            return nullptr;
        void *addr = (char *)_file_map + _offset;
        size_t remain = _file_size - _offset;
        if (remain < _block_size && remain != 0)
        {
            _offset += remain;
            return std::make_shared<DataBlock>(addr, remain, nullptr);
        }
        else
        {
            _offset += _block_size;
            return std::make_shared<DataBlock>(addr, _block_size, nullptr);
        }
    }

    size_t count_blocks() const
    {
        size_t cnt = _file_size / _block_size;
        if (_file_size % _block_size != 0)
            cnt++;
        return cnt;
    }

    ~BlockProducer()
    {
        if (_file_map)
            munmap(_file_map, _file_size);
        if (_fd >= 0)
            close(_fd);
    }
};

class BlockConsumer{
    int _fd;
    size_t _file_size;

    void *_file_map;
    size_t _block_cnt;

    const size_t _hash_size = 256;

public:
    BlockConsumer(char *file_path, size_t n_blocks)
    {
        map_file(file_path, n_blocks);
    }

    void map_file(char *file_path, size_t n_blocks)
    {
        this->~BlockConsumer();
        _fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC);
        if (_fd < 0)
            throw std::runtime_error("Can't open file for writing");
        _file_size = _hash_size * _block_cnt;
        _file_map = mmap(NULL, _file_size, PROT_READ, MAP_SHARED, _fd, _file_size);
    }

    void consume_block()
    {

    }
};

int main(int ac, char **av) {
    if (ac != 3)
    {
        std::cout << "usage: input_file output_file [block_size:1M]" << std::endl;
        return EINVAL;
    }


}
