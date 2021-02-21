#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 5000
int main()
{
    srand(time(NULL));
    int tid, sum = 0, avr = 0;
    int a[SIZE];
    for (int i = 0; i < SIZE; i++)
        a[i] = i;
#pragma omp parallel private(tid) num_threads(10)
    {
        tid = omp_get_thread_num();
        printf("Thread %d: starting...\n", tid);
#pragma omp for reduction(+ \
                          : sum)
        for (int i = 0; i < SIZE; i++)
            sum += a[i];
    }
    avr = sum / (float)SIZE;
    printf("average is %d\n and sum is %d\n", avr, sum);
    return 0;
}