cmake_minimum_required(VERSION 3.16)
project(CompMatrix)
set(CMAKE_CXX_STANDARD 14)

add_executable(CompMatrix main.cpp rsa/rsa.cpp rsa/rsa.h paillier/paillier.cpp paillier/paillier.h matrixSemihomo/matrix.cpp matrixSemihomo/matrix.h)
target_link_libraries(CompMatrix -lm -lgmp -lntl -lpthread)
