//
// Created by Adam Escobedo on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_SIEVER_H
#define SIEVE_OF_ERATOSTHENES_SIEVER_H

#include <unordered_map>
#include "DLList/DLList.h"

class Siever{
private:
    DLList<int> data;
    Node<int>* currentConsider = nullptr;
public:
    std::unordered_map<int, std::pair<Node<int> *,  bool>> nodeMap;

    explicit Siever(int size);
    DLList<int>::Iterator erase(const DLList<int>::Iterator& iterator);
    DLList<int>::Iterator begin() { return data.begin(); }
    DLList<int>::Iterator end() { return data.end(); }
    DLList<int>::Iterator nextFilter();
    void printContents();
};

Siever::Siever(int size) {
    this->data.push_back(2);
    this->currentConsider = this->data.last().ptr;
    this->nodeMap[2] = std::pair<Node<int> *,  bool>(this->currentConsider, true);
    for (int i = 3; i <= size; ++i) {
        this->data.push_back(i);
        this->nodeMap[i] = std::pair<Node<int> *,  bool>(this->data.last().ptr, true);
    }
}

DLList<int>::Iterator Siever::erase(const DLList<int>::Iterator &iterator) {
    this->nodeMap[*iterator] = std::pair<Node<int> *,  bool>(nullptr, false);
    return this->data.erase_at(iterator);
}

DLList<int>::Iterator Siever::nextFilter() {
    auto toReturn = this->currentConsider;
    this->currentConsider = this->currentConsider->get_next();
    return DLList<int>::Iterator(toReturn);
}

void Siever::printContents() {
    for (const auto& it: data) {
        std::cout << it << " ";
    }
}

#endif //SIEVE_OF_ERATOSTHENES_SIEVER_H
