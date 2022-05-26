cmake_minimum_required(VERSION 3.21)
project(veeam)

set(CMAKE_CXX_STANDARD 17)

add_executable(veeam main.cpp BlockReader.cpp BlockReader.hpp BlockWriter.cpp BlockWriter.hpp ProduceConsumePipe.hpp ProduceConsumePipe.cpp DataBlock.cpp DataBlock.hpp)
