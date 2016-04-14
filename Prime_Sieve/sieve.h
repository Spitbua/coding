/*
 * sieve.h
 *
 *  Created on: 11. Jan. 2016
 *  Author: Spitzer Thomas Manfred, SWD14
 *
 */

#ifndef SIEVE_H_
#define SIEVE_H_

#include <stdint.h>
#include <stddef.h>

#define SIEVE_OK 0
#define SIEVE_INVALID_ARGUMENT 1
#define SIEVE_OUT_OF_MEMORY 2

uint64_t* sieve(uint64_t limit, int* status, size_t* primeCount);

#endif /* SIEVE_H_ */
