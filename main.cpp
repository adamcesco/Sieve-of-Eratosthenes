//
// Created by Adam Escobedo on 5/23/2022.
//

#include <iostream>
#include "Siever.h"

int main(){
    int primeSize = 113;
    Siever siever(primeSize);

    for (auto i = siever.nextFilter(); (i != siever.end()) && (*i * *i < primeSize); i = siever.nextFilter()) {
        for (int k = *i * 2; k < primeSize; k += *i) {
            if(k % *i == 0) {
                auto j = DLList<int>::Iterator(siever.nodeMap[k].first);
                if(j.ptr != nullptr)
                    siever.erase(j);
            }
        }
    }

    siever.printContents();

    return 0;
}