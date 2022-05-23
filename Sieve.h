//
// Created by Adam Escobedo on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_SIEVE_H
#define SIEVE_OF_ERATOSTHENES_SIEVE_H

#include <unordered_map>
#include "DLList/DLList.h"

class Sieve{
private:
    DLList<int> data;
    Node<int>* currentFilter = nullptr;
    std::unordered_map<int, Node<int> *> nodeMap;
public:

    explicit Sieve(int size);
    DLList<int>::Iterator erase(const DLList<int>::Iterator& iterator);
    DLList<int>::Iterator begin() { return data.begin(); }
    DLList<int>::Iterator end() { return data.end(); }
    DLList<int>::Iterator nextFilter();
    DLList<int>::Iterator iteratorAt(int i);
    void printContents();
};

Sieve::Sieve(int size) {
    if(size > 1){
        this->data.push_back(2);
        this->currentFilter = this->data.last().ptr;
        this->nodeMap[2] = this->currentFilter;
        for (int i = 3; i <= size; ++i) {
            this->data.push_back(i);
            this->nodeMap[i] = this->data.last().ptr;
        }
    }
    else{
        throw std::invalid_argument("Error in \"Sieve::Sieve(int size)\" | passed size was less than 2");
    }
}

DLList<int>::Iterator Sieve::erase(const DLList<int>::Iterator &iterator) {
    this->nodeMap[*iterator] = nullptr;
    return this->data.erase_at(iterator);
}

DLList<int>::Iterator Sieve::nextFilter() {
    auto toReturn = this->currentFilter;
    this->currentFilter = this->currentFilter->get_next();
    return DLList<int>::Iterator(toReturn);
}

void Sieve::printContents() {
    for (const auto& it: data) {
        std::cout << it << " ";
    }
}

DLList<int>::Iterator Sieve::iteratorAt(int i) {
    return DLList<int>::Iterator(this->nodeMap[i]);
}

#endif //SIEVE_OF_ERATOSTHENES_SIEVE_H
