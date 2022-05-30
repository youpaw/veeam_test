//
// Created by youpaw on 5/30/22.
//

#include "FileWriter.hpp"
#include <exception>

FileWriter::FileWriter(std::string &file_path)
{
	_output = std::ofstream(file_path, std::ios::out | std::ios::ate | std::ios::trunc | std::ios::binary);
	if (!_output)
	{
		perror(file_path.c_str());
		throw std::runtime_error("Cannot open destination file for writing");
	}
}

void FileWriter::write(const char *bytes, size_t size)
{
	_output.write(bytes, size);
}

FileWriter::~FileWriter()
{
	_output.close();
}
