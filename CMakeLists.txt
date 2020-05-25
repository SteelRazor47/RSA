cmake_minimum_required(VERSION 3.1)
project(rsa LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(GMP REQUIRED)
add_executable(rsa src/main.cpp src/RSA.cpp src/Utility.cpp src/Message.cpp)

target_link_libraries(rsa gmp gmpxx)
target_compile_features(rsa PRIVATE cxx_std_17)
