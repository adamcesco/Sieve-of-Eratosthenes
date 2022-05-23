//
// Created by Adam Escobedo on 5/23/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_SIEVE_H
#define SIEVE_OF_ERATOSTHENES_SIEVE_H

#include <unordered_map>
#include "DLList/DLList.h"

class Sieve{
private:
    std::unordered_map<int, std::pair<Node<int> *,  bool>> nodeMap;
    DLList<int> data;
    Node<int>* currentConsider = nullptr;
public:
    explicit Sieve(int size);
    DLList<int>::Iterator erase(const DLList<int>::Iterator& iterator);
    DLList<int>::Iterator begin() { return data.begin(); }
    DLList<int>::Iterator end() { return data.end(); }
    DLList<int>::Iterator nextToConsider();
    void printContents();
};

Sieve::Sieve(int size) {
    this->data.push_back(2);
    this->currentConsider = this->data.last().ptr;
    this->nodeMap[2] = std::pair<Node<int> *,  bool>(this->currentConsider, true);
    for (int i = 3; i <= size; ++i) {
        this->data.push_back(i);
        this->nodeMap[i] = std::pair<Node<int> *,  bool>(this->data.last().ptr, true);
    }
}

DLList<int>::Iterator Sieve::erase(const DLList<int>::Iterator &iterator) {
    this->nodeMap[*iterator] = std::pair<Node<int> *,  bool>(nullptr, false);
    return this->data.erase_at(iterator);
}

DLList<int>::Iterator Sieve::nextToConsider() {
    auto& element = this->nodeMap[this->currentConsider->get()];
    if (element.second == false){
        this->currentConsider = this->currentConsider->get_next();
        if(this->currentConsider != this->data.end().ptr)
            this->nodeMap[this->currentConsider->get()].second = false;
    }
    else{
        element.second = false;
    }
    return DLList<int>::Iterator(this->currentConsider);
}

void Sieve::printContents() {
    for (const auto& it: data) {
        std::cout << it << " ";
    }
}

#endif //SIEVE_OF_ERATOSTHENES_SIEVE_H
