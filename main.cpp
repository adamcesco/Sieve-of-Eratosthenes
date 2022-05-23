//
// Created by Adam Escobedo on 5/23/2022.
//

#include <iostream>
#include "Sieve.h"

int main(){
    int size = 113;     //<- must be a prime number
    Sieve sieve(size);

    int filterNum = *sieve.getNextFilter();
    while (filterNum * filterNum < size) {
        for (int multiple = filterNum * filterNum; multiple < size; multiple += filterNum) {
            auto toDelete = sieve.iteratorMappedTo(multiple);
            if (toDelete.ptr != nullptr)
                sieve.erase(toDelete);
        }
        filterNum = *sieve.getNextFilter();
    }

    sieve.printContents();

    return 0;
}