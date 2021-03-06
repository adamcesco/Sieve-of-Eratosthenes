//
// Created by misc1 on 5/23/2022.
//

#include "EratosthenesSieve.h"
#include <iostream>

EratosthenesSieve::EratosthenesSieve(int n) {
    if(n < 2)
        throw std::invalid_argument("Error in \"Sieve::Sieve(int n)\" | passed n was less than 2");

    this->n = n;
    for (int i = 2; i <= this->n; ++i) {
        this->data.push_back(i);
        this->nodeMap[i] = this->data.last().ptr;
    }
    this->currentFilter = this->nodeMap[2];
}

void EratosthenesSieve::sieve() {
    this->iterationsCounter = 0;
    int filterNum = *this->advance();
    while (filterNum * filterNum < n) {
        for (int multiple = filterNum * filterNum; multiple < n; multiple += filterNum) {
            auto toDelete = this->nodeMap[multiple];
            if (toDelete != nullptr)
                this->erase(toDelete);

            this->iterationsCounter++;
        }
        filterNum = *this->advance();
    }
}

DLList<int>::Iterator EratosthenesSieve::advance() {
    auto toReturn = this->currentFilter;
    this->currentFilter = this->currentFilter->get_next();
    return DLList<int>::Iterator(toReturn);
}

DLList<int>::Iterator EratosthenesSieve::erase(Node<int> *iterator) {
    this->nodeMap[iterator->get()] = nullptr;
    return DLList<int>::Iterator(this->data.erase_at(iterator));
}

void EratosthenesSieve::print() {
    std::cout << "Sieve of Eratosthenes" << std::endl;
    std::cout << "\tn: " << this->n << std::endl;
    std::cout << "\tnumber of iterations: " << this->iterationsCounter << std::endl;
    std::cout << '\t';
    for (const auto& it: this->data)
        std::cout << it << " ";
    std::cout << std::endl;
}