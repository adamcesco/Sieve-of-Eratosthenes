//
// Created by Adam Escobedo on 5/23/2022.
//

#include "Sieves/EratosthenesSieve/EratosthenesSieve.h"
#include "Sieves/OptimizedSieve/OptimizedSieve.h"
#include <iostream>
#include <fstream>

int main(){
    //showcasing each sieve and their relative nature
    {
        int n = 113;     //<- must be a prime number

        EratosthenesSieve eratosthenesSieve(n);
        eratosthenesSieve.sieve();
        eratosthenesSieve.print();
        std::cout << std::endl;

        //OptimizedSieve class is more optimal to use for any given n larger than 499
        OptimizedSieve optimizedSieve(n);
        optimizedSieve.sieve();
        optimizedSieve.print();
        std::cout << std::endl;
    }
    {
        int n = 677;     //<- must be a prime number

        EratosthenesSieve eratosthenesSieve(n);
        eratosthenesSieve.sieve();
        eratosthenesSieve.print();
        std::cout << std::endl;

        //OptimizedSieve class is more optimal to use for any given n larger than 499
        OptimizedSieve optimizedSieve(n);
        optimizedSieve.sieve();
        optimizedSieve.print();
        std::cout << std::endl;
    }


    //generating csv files with data showing the time complexity for the sieves when given growing n values
    {
        std::ofstream outFile1;
        outFile1.open("../data/Eratosthenes-Sieve-Statistics.csv");
        if (!outFile1.is_open()) {
            throw std::invalid_argument(
                    "Error in \"int main()\" | could not open \"../Eratosthenes-Sieve-Statistics.csv\"");
        }

        std::ofstream outFile2;
        outFile2.open("../data/Optimized-Sieve-Statistics.csv");
        if (!outFile2.is_open()) {
            throw std::invalid_argument(
                    "Error in \"int main()\" | could not open \"../Optimized-Sieve-Statistics.csv\"");
        }

        for (int n = 2; n < 10000; ++n) {
            EratosthenesSieve eratosthenesSieve(n);
            eratosthenesSieve.sieve();
            outFile1 << n << ',' << eratosthenesSieve.readIterationsCounter() << std::endl;


            OptimizedSieve optimizedSieve(n);
            optimizedSieve.sieve();
            optimizedSieve.readIterationsCounter();
            outFile2 << n << ',' << optimizedSieve.readIterationsCounter() << std::endl;
        }
        outFile1.close();
        outFile2.close();
    }

    return 0;
}