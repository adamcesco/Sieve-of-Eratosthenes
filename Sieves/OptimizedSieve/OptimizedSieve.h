//
// Created by misc1 on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_OPTIMIZEDSIEVE_H
#define SIEVE_OF_ERATOSTHENES_OPTIMIZEDSIEVE_H

#include <vector>

class OptimizedSieve {
private:
    std::vector<long long >* isPrime = nullptr;
    std::vector<long long >* prime = nullptr;
    std::vector<long long >* SPF = nullptr;
    int iterationsCounter = 0;
    int n = 0;

public:
    explicit OptimizedSieve(int n);
    ~OptimizedSieve();
    void sieve();
    void print();
    int readN() const { return this->n; }
    int readIterationsCounter() const { return this->iterationsCounter; }
};


#endif //SIEVE_OF_ERATOSTHENES_OPTIMIZEDSIEVE_H
