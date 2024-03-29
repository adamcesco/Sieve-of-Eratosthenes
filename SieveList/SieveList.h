//
// Created by misc1 on 9/10/2022.
//

#ifndef SIEVE_OF_ERATOSTHENES_SIEVELIST_H
#define SIEVE_OF_ERATOSTHENES_SIEVELIST_H


class SieveList {
public:
    struct SieveNode {
        int val = -1;
        SieveNode *next = nullptr;
        SieveNode *prev = nullptr;
        SieveNode() = default;
        explicit SieveNode(int x) : val(x) {}
        SieveNode(int x, SieveNode *next, SieveNode *prev) : val(x), next(next), prev(prev) {}
    };

    //constructor
    SieveList(SieveList::SieveNode *node);

    //rule of 3
    SieveList(const SieveList& list);
    SieveList& operator=(const SieveList& list);
    ~SieveList();

    void erase(SieveNode* node);
    void push_back(SieveNode* node);
    SieveNode* front() { return dummy->next; }
    SieveNode* back() { return dummy->prev; }
    SieveNode* end() { return dummy; }

private:
    SieveNode* dummy = nullptr;
};


#endif //SIEVE_OF_ERATOSTHENES_SIEVELIST_H
