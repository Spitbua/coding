/*
 * main.c
 *
 *  Created on: 11. Jän. 2016
 *  Author: Spitzer Thomas Manfred, SWD14
 *
 */

#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sieve.h"

#ifndef DEBUG
//#define DEBUG
#endif /* DEBUG */

int main(int argc, char* argv[]) {
	size_t primeCount = 0;
	uint64_t primeLimit = 0;
	int status = SIEVE_OK;
	bool printPrimeNumbers = false;
	uint64_t* primes = NULL;
	clock_t prgstart = 0, prgende = 0;


    #ifdef DEBUG
	    printf("Arguments count: %d \n", argc);
    #endif

	if (argc < 2 || argc > 3) {
		status = SIEVE_INVALID_ARGUMENT;
		printf("Too less or to many parameters for using the magic of Eratosthenes. \n");
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if (isdigit(*argv[i])) {
			primeLimit = strtoull(argv[i], NULL, 10);
			//primeLimit+=1;
		} else if ((strcmp(argv[i], "-p")) == 0) {
			printPrimeNumbers = true;
		}
	}

	if (primeLimit < 2) {
		status = SIEVE_INVALID_ARGUMENT;
	}

    #ifdef DEBUG
        printf("%d\n", primeLimit);
        printf("%d\n", printPrimeNumbers);
    #endif

	if (status == SIEVE_OK) {
		prgstart=clock(); //CPU-Zeit zu Beginn des Programmes
		primes = sieve(primeLimit, &status, &primeCount);
		prgende=clock();
	}

	if (status == SIEVE_INVALID_ARGUMENT) {
		printf("Invalid Arguments!\n");
		return 1;
	} else if (status == SIEVE_OUT_OF_MEMORY) {
		printf("Memory allocation error!\n");
		return 1;
	}

	printf("Number of primes between 2 and %" PRIu64 ": %"PRIu64 "\n",
			primeLimit, primeCount);

	if (printPrimeNumbers) {
		for (int i = 0; i < primeCount; i++) {
			printf("%" PRIu64 "\n", primes[i]);
		}
	}

	free(primes);

    printf("Runtime: %.2f seconds\n",(float)(prgende-prgstart) / CLOCKS_PER_SEC);

    #ifdef DEBUG
        printf("Program finished");
    #endif

	return 0;
}

