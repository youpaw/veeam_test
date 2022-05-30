//
// Created by youpaw on 5/29/22.
//

#include "ArgParser.hpp"
#include <iostream>

ArgParser::ArgParser(int ac, char **av)
{
	if (ac < 3 || ac > 4)
	{
		print_usage();
		exit(EINVAL);
	}
	input_file = std::string(av[1]);
	output_file = std::string(av[2]);
	block_size = ac == 3 ? MEGABYTE : std::strtoull(av[3], nullptr, 10) * MEGABYTE;
}

void ArgParser::print_usage()
{
	std::cout << "Usage: input_file output_file [block_size (in megabytes)]" << std::endl;
}
