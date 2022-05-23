//
// Created by Adam Escobedo on 5/23/2022.
//

#include "OptimizedSieve.h"
#include <stdexcept>
#include <iostream>

OptimizedSieve::OptimizedSieve(int n) {
    if(n < 2)
        throw std::invalid_argument("Error in \"Sieve::Sieve(int n)\" | passed n was less than 2");

    this->n = n;
    this->isPrime = new std::vector<bool>(this->n, true);
    this->prime = new std::vector<long long int>();
    this->SPF = new std::vector<long long int>(this->n);
}

OptimizedSieve::~OptimizedSieve() {
    delete this->isPrime;
    delete this->prime;
    delete this->SPF;
}

void OptimizedSieve::print() {
    std::cout << "Optimized Sieve of Eratosthenes" << std::endl;
    std::cout << "\tnumber of iterations: " << this->iterationsCounter << std::endl;
    std::cout << '\t';
    for (const auto& it: *this->prime)
        std::cout << it << " ";
    std::cout << std::endl;
}

void OptimizedSieve::sieve() {
    auto& isPrimeAlias = *this->isPrime;
    auto& primeAlias = *this->prime;
    auto& SPFAlias = *this->SPF;

    this->iterationsCounter = 0;
    isPrimeAlias[0] = isPrimeAlias[1] = false;

    for (long long int i = 2; i < this->n; i++) {
        if (isPrimeAlias[i]) {
            primeAlias.push_back(i);
            SPFAlias[i] = i;
        }

        for (long long int j=0;
             (j < prime->size()) && (i * primeAlias[j] < n) && (primeAlias[j] <= SPFAlias[i]);
             j++)
        {
            isPrimeAlias[i * primeAlias[j]] = false;
            SPFAlias[i * primeAlias[j]] = primeAlias[j] ;
            ++this->iterationsCounter;
        }
    }
}
