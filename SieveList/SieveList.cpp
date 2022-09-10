//
// Created by misc1 on 9/10/2022.
//

#include "SieveList.h"
#include <iostream>

SieveList::SieveList(SieveList::SieveNode *dummy) : dummy(dummy){
    this->dummy->prev = this->dummy;
    this->dummy->next = this->dummy;
}

SieveList::SieveList(const SieveList &list) {
    this->dummy = new SieveNode();
    this->dummy->prev = this->dummy;
    this->dummy->next = this->dummy;
    SieveNode* iter = list.dummy->next;
    while (iter != list.dummy) {
        this->push_back(new SieveNode(iter->val));
        iter = iter->next;
    }
}

SieveList& SieveList::operator=(const SieveList& list) {
    if(this == &list){
        return *this;
    }

    {
        SieveNode* iter = dummy->next;
        dummy->next = nullptr;
        while (iter != nullptr) {
            SieveNode* next = iter->next;
            delete iter;
            iter = next;
        }
    }
    {
        this->dummy = new SieveNode();
        this->dummy->prev = this->dummy;
        this->dummy->next = this->dummy;
        SieveNode *iter = list.dummy->next;
        while (iter != list.dummy) {
            this->push_back(new SieveNode(iter->val));
            iter = iter->next;
        }
    }
    return *this;
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
