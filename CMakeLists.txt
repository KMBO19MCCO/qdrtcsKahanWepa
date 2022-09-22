cmake_minimum_required(VERSION 3.22)
project(qdrtcsKahanWepa)
set(CMAKE_CXX_STANDARD 23)

include_directories(inc)
link_directories(lib)
link_libraries(libexcerpt.a)
add_executable(qdrtcsKahanWepa src/test.cpp src/solver.cpp)