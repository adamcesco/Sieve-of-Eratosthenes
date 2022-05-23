//
// Created by Adam Escobedo on 5/23/2022.
//

#include "Sieves/EratosthenesSieve/EratosthenesSieve.h"
#include "Sieves/OptimizedSieve/OptimizedSieve.h"
#include <iostream>

int main(){
    int n = 113;     //<- must be a prime number

    EratosthenesSieve eratosthenesSieve(n);
    eratosthenesSieve.sieve();
    eratosthenesSieve.print();

    std::cout << std::endl;

    OptimizedSieve optimizedSieve(n);
    optimizedSieve.sieve();
    optimizedSieve.print();

    return 0;
}