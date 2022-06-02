cmake_minimum_required(VERSION 3.21)
project(veeam)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL)

add_executable(veeam main.cpp BlockReader.cpp BlockReader.hpp BlockHasher.cpp BlockHasher.hpp ProduceConsumePipe.hpp ProduceConsumePipe.cpp DataBlock.cpp DataBlock.hpp ArgParser.cpp ArgParser.hpp FileWriter.cpp FileWriter.hpp main.hpp)

target_link_libraries(veeam ssl crypto)