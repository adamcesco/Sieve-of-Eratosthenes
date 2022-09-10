//
// Created by misc1 on 9/10/2022.
//

#ifndef BETTERDLL_SIEVELIST_H
#define BETTERDLL_SIEVELIST_H


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

    SieveList(SieveList::SieveNode *node);
    void erase(SieveNode* node);
    void push_back(SieveNode* node);
    SieveNode* front() { return dummy->next; }
    SieveNode* back() { return dummy->prev; }
    SieveNode* end() { return dummy; }
    ~SieveList();

private:
    SieveNode* dummy = nullptr;
};


#endif //BETTERDLL_SIEVELIST_H
