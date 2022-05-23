//
// Created by Adam Escobedo on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_SIEVE_H
#define SIEVE_OF_ERATOSTHENES_SIEVE_H

#include <unordered_map>
#include "DLList/DLList.h"

class Sieve{
private:
    std::unordered_map<int, Node<int> *> nodeMap;
    DLList<int> data;
public:
    explicit Sieve(int size);
};

Sieve::Sieve(int size) {
    for (int i = 2; i < size; ++i) {
        this->data.push_back(i);
        this->nodeMap[i] = this->data.last().ptr;
    }
}

#endif //SIEVE_OF_ERATOSTHENES_SIEVE_H
