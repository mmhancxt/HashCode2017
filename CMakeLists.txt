cmake_minimum_required(VERSION 3.6)
project(HashCode2017)

find_package(Boost 1.63.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        HashCode2017/main.cpp HashCode2017/InputLoader.h HashCode2017/Algo.h HashCode2017/Objects.h)

add_executable(HashCode2017 ${SOURCE_FILES})
target_link_libraries(HashCode2017 ${Boost_LIBRARIES})