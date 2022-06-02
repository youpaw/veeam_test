//
// Created by youpaw on 5/29/22.
//

#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <string>
#include <cstddef>

struct ArgParser{
	std::string input_file{};
	std::string output_file{};
	size_t block_size = 0;
	ArgParser(int ac, char **av);
	static void print_usage();
};

#endif //ARGPARSER_HPP
