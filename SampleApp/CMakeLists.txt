cmake_minimum_required(VERSION 3.26)
project(SampleApp)

set(CMAKE_CXX_STANDARD 23)

add_executable(SampleApp main.cpp)
target_link_libraries(SampleApp OccViewerQt)