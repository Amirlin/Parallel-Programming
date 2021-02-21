#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

// min prime number
#define PRIME_MIN 3
// max prime number
#define PRIME_MAX 97
// size of primes array
#define SIZE 100

int main()
{
    size_t primes[SIZE], nb_primes = 0;
    size_t divisor;
    bool is_prime;
#pragma omp parallel for private(divisor, is_prime) ordered schedule(dynamic)
    for (size_t i = PRIME_MIN; i < PRIME_MAX; i += 2)
    {
        is_prime = true;
        divisor = PRIME_MIN;
        while ((divisor < i) && is_prime)
        {
            if ((i % divisor) == 0)
                is_prime = false;
            divisor += 2;
        }
#pragma omp ordered
#pragma omp critical
        if (is_prime)
        {
            primes[nb_primes] = i;
            nb_primes++;
        }
    }
    printf("Nb primes=%ld\n", nb_primes);
}