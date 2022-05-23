//
// Created by Adam Escobedo on 5/23/2022.
//

#include "Sieves/EratosthenesSieve/EratosthenesSieve.h"

int main(){
    int n = 113;     //<- must be a prime number
    EratosthenesSieve eratosthenesSieve(n);
    eratosthenesSieve.sieve();
    eratosthenesSieve.print();

    return 0;
}