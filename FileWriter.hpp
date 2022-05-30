//
// Created by youpaw on 5/30/22.
//

#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <fstream>

class FileWriter{
	std::ofstream _output;

public:
	explicit FileWriter(std::string &file_path);

	void write(const char *bytes, size_t size);

	~FileWriter();
};

#endif //FILEWRITER_HPP
