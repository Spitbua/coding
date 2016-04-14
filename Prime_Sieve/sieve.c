/*
 * sieve.h
 *
 *  Created on: 11. Jän. 2016
 *  Author: Spitzer Thomas Manfred, SWD14
 *
 */

#include <math.h>
#include <memory.h>
#include <stdlib.h>

#include "sieve.h"

uint64_t *sieve(uint64_t limit, int *status, size_t *primeCount) {
	uint64_t *primes = NULL;

	if (limit < 2) {
		*status = SIEVE_INVALID_ARGUMENT;
	} else {
		//allocate memory for char array with size of limit+1
		unsigned char *numbers = malloc((limit + 1) * sizeof(unsigned char));
		if (!numbers) {
			*status = SIEVE_OUT_OF_MEMORY;
		} else {
			//set all values in char array to 1
			memset(numbers, 1, limit + 1);

			//build square root of limit
			uint64_t squareRoot = (uint64_t) sqrt((double) limit);
			for (uint64_t i = 2; i <= squareRoot; i++) {
				if (numbers[i]) {
					//count number of primes found < squareRoot
					(*primeCount)++;
					//search for multiple of i
					for (uint64_t j = i * i; j <= limit; j += i) {
						numbers[j] = 0;
					}
				}
			}

			//count number of primes found > squareRoot < limit
			for (uint64_t i = squareRoot + 1; i <= limit; i++) {
				if (numbers[i]) {
					(*primeCount)++;
				}
			}

			//allocate memory for uint64_t array
			//with size of number of primes found
			primes = malloc((*primeCount) * sizeof(uint64_t));
			if (!primes) {
				*status = SIEVE_OUT_OF_MEMORY;
			} else {
				for (uint64_t i = 2, j = 0; i <= limit; i++) {
					//all values set to 1 are primes
					if (numbers[i]) {
						primes[j] = i;
						j++;
					}
				}
				*status = SIEVE_OK;
			}
			free(numbers);
		}
	}

	return primes;
}
