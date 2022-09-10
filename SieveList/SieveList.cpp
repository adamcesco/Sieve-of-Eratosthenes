//
// Created by misc1 on 9/10/2022.
//

#include "SieveList.h"
#include <iostream>

SieveList::SieveList(SieveList::SieveNode *dummy) : dummy(dummy){
    this->dummy->prev = this->dummy;
    this->dummy->next = this->dummy;
}

void SieveList::erase(SieveList::SieveNode *node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
}

void SieveList::push_back(SieveNode* node) {
    this->dummy->prev->next = node;
    node->prev = this->dummy->prev;
    this->dummy->prev = node;
    node->next = this->dummy;
}

SieveList::~SieveList() {
    SieveNode* iter = dummy->next;
    dummy->next = nullptr;
    while (iter != nullptr) {
        SieveNode* next = iter->next;
        delete iter;
        iter = next;
    }
}
