//
// Created by misc1 on 5/23/2022.
//

#include "EratosthenesSieve.h"
#include <iostream>

EratosthenesSieve::EratosthenesSieve(int n) : data(new SieveList::SieveNode){
    if(n < 2)
        throw std::invalid_argument("Error in \"Sieve::Sieve(int n)\" | passed n was less than 2");

    this->n = n;
    for (int i = 2; i <= this->n; ++i) {
        this->data.push_back(new SieveList::SieveNode(i));
        this->nodeMap[i] = this->data.back();
    }
    this->currentFilter = this->nodeMap[2];
}

void EratosthenesSieve::sieve() {
    this->iterationsCounter = 0;
    int filterNum = this->advance()->val;
    while (filterNum * filterNum < n) {
        for (int multiple = filterNum * filterNum; multiple < n; multiple += filterNum) {
            SieveList::SieveNode* toDelete = this->nodeMap[multiple];
            if (toDelete != nullptr)
                this->erase(toDelete);

            this->iterationsCounter++;
        }
        filterNum = this->advance()->val;
    }
}

SieveList::SieveNode* EratosthenesSieve::advance() {
    SieveList::SieveNode* toReturn = this->currentFilter;
    this->currentFilter = this->currentFilter->next;
    return toReturn;
}

void EratosthenesSieve::erase(SieveList::SieveNode* node) {
    this->nodeMap[node->val] = nullptr;
    this->data.erase(node);
}

void EratosthenesSieve::print() {
    std::cout << "Sieve of Eratosthenes" << std::endl;
    std::cout << "\tn: " << this->n << std::endl;
    std::cout << "\tnumber of iterations: " << this->iterationsCounter << std::endl;
    std::cout << '\t';

    SieveList::SieveNode* iter = this->data.front();
    while (iter != this->data.end()) {
        std::cout << iter->val << " ";
        iter = iter->next;
    }
    std::cout << std::endl;
}