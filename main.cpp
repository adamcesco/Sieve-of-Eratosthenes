//
// Created by Adam Escobedo on 5/23/2022.
//

#include <iostream>
#include "Sieve.h"

int main(){
    int primeSize = 113;
    Sieve sieve(primeSize);

    for (auto i = sieve.nextFilter(); (i != sieve.end()) && (*i * *i < primeSize); i = sieve.nextFilter()) {
        int filter = *i;
        for (int k = filter * filter; k < primeSize; k += filter) {
            if(k % filter == 0) {
                auto j = sieve.iteratorAt(k);
                if(j.ptr != nullptr)
                    sieve.erase(j);
            }
        }
    }

    sieve.printContents();

    return 0;
}