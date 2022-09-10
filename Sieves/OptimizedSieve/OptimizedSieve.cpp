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
    this->isPrime = std::vector<bool>(this->n, true);
    this->SPF = std::vector<long long int>(this->n);
}

void OptimizedSieve::sieve() {
    this->iterationsCounter = 0;
    this->isPrime[0] = this->isPrime[1] = false;

    for (long long int i = 2; i < this->n; i++) {
        if (this->isPrime[i]) {
            this->prime.push_back(i);
            this->SPF[i] = i;
        }

        bool loopEntered = false;
        for (long long int j=0;
             (j < this->prime.size()) && (i * this->prime[j] < this->n) && (this->prime[j] <= this->SPF[i]);
             j++)
        {
            loopEntered = true;
            this->isPrime[i * this->prime[j]] = false;
            this->SPF[i * this->prime[j]] = this->prime[j];
            ++this->iterationsCounter;
        }
        if(loopEntered == false)
            ++this->iterationsCounter;
    }
}

void OptimizedSieve::print() {
    std::cout << "Optimized Sieve of Eratosthenes" << std::endl;
    std::cout << "\tn: " << this->n << std::endl;
    std::cout << "\tnumber of iterations: " << this->iterationsCounter << std::endl;
    std::cout << '\t';
    for (const auto& it: this->prime)
        std::cout << it << " ";
    std::cout << std::endl;
}
