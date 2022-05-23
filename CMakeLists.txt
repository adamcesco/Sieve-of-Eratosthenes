cmake_minimum_required(VERSION 3.16)
project(Sieve-of-Eratosthenes)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sieve-of-Eratosthenes main.cpp DLList/DLList.h DLList/Node.h Sieves/EratosthenesSieve/EratosthenesSieve.h Sieves/EratosthenesSieve/EratosthenesSieve.cpp Sieves/OptimizedSieve/OptimizedSieve.h Sieves/OptimizedSieve/OptimizedSieve.cpp)
