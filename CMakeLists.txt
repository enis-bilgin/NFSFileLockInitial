cmake_minimum_required(VERSION 3.8)
project(FileLockMulti)

set(CMAKE_CXX_STANDARD 14)

add_executable(FileLockMulti main.cpp)

target_link_libraries(
        FileLockMulti
        glog
        gflags
)
