# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (PrimeC)

#set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

# 指定生成目标
aux_source_directory(../src DIR_SRCS)
aux_source_directory(../src/comm DIR_SRCS)
aux_source_directory(../src/platform DIR_SRCS)
add_executable(prime ${DIR_SRCS})