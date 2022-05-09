cmake_minimum_required(VERSION 3.16)
project(CompMatrix)
set(CMAKE_CXX_STANDARD 14)

add_executable(CompMatrix main.cpp rsa/rsa.cpp rsa/rsa.h paillier/paillier.cpp paillier/paillier.h matrixSemihomo/matrix.cpp matrixSemihomo/matrix.h bgv/bgv.cpp bgv/bgv.h matrixFullhomo/matrixfull.cpp matrixFullhomo/matrixfull.h)
target_link_libraries(CompMatrix -lm -lgmp -lntl -lpthread)
find_package(SEAL 4.0 REQUIRED)

#if(NOT DEFINED SEAL_BUILD_EXAMPLES)
#    set(SEAL_BUILD_EXAMPLES ON)
#
#    # Import Microsoft SEAL
#    find_package(SEAL 3.7.2 EXACT REQUIRED)
#
#    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
#endif()

if(TARGET SEAL::seal)
    target_link_libraries(CompMatrix SEAL::seal)
elseif(TARGET SEAL::seal_shared)
    target_link_libraries(CompMatrix SEAL::seal_shared)
else()
    message(FATAL_ERROR "Cannot find target SEAL::seal or SEAL::seal_shared")
endif()