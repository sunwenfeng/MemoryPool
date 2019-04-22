cmake_minimum_required(VERSION 3.6)
project(MemoryPool)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp C-98/MemoryPool.h C-98/MemoryPool.tcc StackAlloc.h)
add_executable(MemoryPool ${SOURCE_FILES})