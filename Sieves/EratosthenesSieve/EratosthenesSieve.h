//
// Created by misc1 on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_ERATOSTHENESSIEVE_H
#define SIEVE_OF_ERATOSTHENES_ERATOSTHENESSIEVE_H


#include <unordered_map>
#include "../../SieveList/SieveList.h"

class EratosthenesSieve{
private:
    SieveList::SieveNode* currentFilter = nullptr;
    SieveList data;
    std::unordered_map<int, SieveList::SieveNode*> nodeMap;
    int iterationsCounter = 0;
    int n = 0;

    void erase(SieveList::SieveNode* node);
    SieveList::SieveNode* advance();
public:
    explicit EratosthenesSieve(int n);

    void sieve();
    void print();
    int readN() const { return this->n; }
    int readIterationsCounter() const { return this->iterationsCounter; }
    SieveList& getPrimes() { return this->data; }
};


#endif //SIEVE_OF_ERATOSTHENES_ERATOSTHENESSIEVE_H
