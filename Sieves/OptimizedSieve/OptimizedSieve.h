//
// Created by misc1 on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_OPTIMIZEDSIEVE_H
#define SIEVE_OF_ERATOSTHENES_OPTIMIZEDSIEVE_H

#include <vector>

class OptimizedSieve {
private:
    std::vector<bool> isPrime;
    std::vector<long long int> prime;
    std::vector<long long int> SPF;
    int iterationsCounter = 0;
    int n = 0;

public:
    explicit OptimizedSieve(int n);

    void sieve();
    void print();
    int readN() const { return this->n; }
    int readIterationsCounter() const { return this->iterationsCounter; }
    std::vector<long long int>& getPrimes() { return this->prime; }
};


#endif //SIEVE_OF_ERATOSTHENES_OPTIMIZEDSIEVE_H
