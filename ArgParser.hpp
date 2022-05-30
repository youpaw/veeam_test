//
// Created by youpaw on 5/29/22.
//

#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <string>
#include <cstddef>
#define MEGABYTE 1048576

struct ArgParser{
	std::string input_file;
	std::string output_file;
	size_t block_size;
	ArgParser(int ac, char **av);
	static void print_usage();
};

#endif //ARGPARSER_HPP
