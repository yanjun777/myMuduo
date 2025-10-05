
cmake_minimum_required(VERSION 3.10)
project(mymuduo)
# mymuduo 库的输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置调试选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

# 定义参与编译的源文件
aux_source_directory(. SRC_LIST)

#编译动态库
add_library(mymuduo SHARED ${SRC_LIST}) 