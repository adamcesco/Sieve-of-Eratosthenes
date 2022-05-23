//
// Created by misc1 on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_ERATOSTHENESSIEVE_H
#define SIEVE_OF_ERATOSTHENES_ERATOSTHENESSIEVE_H


#include <unordered_map>
#include "../../DLList/DLList.h"

class EratosthenesSieve{
private:
    Node<int>* currentFilter = nullptr;
    DLList<int> data;
    std::unordered_map<int, Node<int> *> nodeMap;
    int iterationsCounter = 0;
    int n = 0;

    DLList<int>::Iterator erase(Node<int>* iterator);
    DLList<int>::Iterator begin() { return data.begin(); }
    DLList<int>::Iterator end() { return data.end(); }
    DLList<int>::Iterator advance();
public:
    explicit EratosthenesSieve(int n);

    void sieve();
    void print();
    int readN() const { return this->n; }
    int readIterationsCounter() const { return this->iterationsCounter; }
    DLList<int>& getPrimes() { return this->data; }
};


#endif //SIEVE_OF_ERATOSTHENES_ERATOSTHENESSIEVE_H
