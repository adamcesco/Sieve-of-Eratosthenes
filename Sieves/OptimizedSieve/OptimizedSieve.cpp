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
    this->isPrime = new std::vector<long long >(1000001, true);
    this->prime = new std::vector<long long >();
    this->SPF = new std::vector<long long >(1000001);
}

OptimizedSieve::~OptimizedSieve() {
    delete this->isPrime;
    delete this->prime;
    delete this->SPF;
}

void OptimizedSieve::print() {
    std::cout << "numbers of iterations: " << this->iterationsCounter << std::endl;
    std::cout << "all prime numbers from 2 to " << this->n << ':' << std::endl;
    for (const auto& it: *this->prime) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

void OptimizedSieve::sieve() {
    iterationsCounter = 0;

    (*isPrime)[0] = (*isPrime)[1] = false ;

    for (long long int i=2; i < n; i++)
    {
        if ((*isPrime)[i])
        {
            (*prime).push_back(i);
            (*SPF)[i] = i;
        }

        for (long long int j=0;
             (j < (int)prime->size()) && (i*(*prime)[j] < n && (*prime)[j] <= (*SPF)[i]);
             j++)
        {
            (*isPrime)[i*(*prime)[j]]=false;
            (*SPF)[i*(*prime)[j]] = (*prime)[j] ;
            iterationsCounter++;
        }
    }
}
