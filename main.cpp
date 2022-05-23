//
// Created by Adam Escobedo on 5/23/2022.
//

#include <iostream>
#include "Sieve.h"

int main(){
    int largestPrime = 113;     //<- must be a prime number
    Sieve sieve(largestPrime);

    int filterNum = *sieve.getNextFilter();
    while (filterNum * filterNum < largestPrime) {
        for (int multiple = filterNum * filterNum; multiple < largestPrime; multiple += filterNum) {
            auto toDelete = sieve.iteratorMappedTo(multiple);
            if (toDelete.ptr != nullptr)
                sieve.erase(toDelete);
        }
        filterNum = *sieve.getNextFilter();
    }

    sieve.printContents();

    return 0;
}