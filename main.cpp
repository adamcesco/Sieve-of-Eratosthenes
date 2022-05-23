//
// Created by Adam Escobedo on 5/23/2022.
//

#include <iostream>
#include "Sieve.h"

int main(){
    int primeSize = 997;
    Sieve sieve(primeSize);

    for (auto i = sieve.nextToConsider(); i != sieve.end(); i = sieve.nextToConsider()) {
        auto j = i;
        j++;
        while(j != sieve.end()){
            if(*j % *i == 0) {
                j = sieve.erase(j);
            }
            else {
                j++;
            }
        }
    }

    sieve.printContents();

    return 0;
}