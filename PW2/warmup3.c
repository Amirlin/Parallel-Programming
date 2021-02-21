#include <stdio.h>
#include <omp.h>
#define SIZE 10000
int main()
{
    int i, tid;
    long t_ref, t_end;
    double a[SIZE], b[SIZE], c[SIZE];
    for (i = 0; i < SIZE; i++)
        a[i] = b[i] = i;
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
            printf("Nb threads = %d\n", omp_get_num_threads());
        printf("Thread %d: starting...\n", tid);
        t_ref = omp_get_wtime();
#pragma omp for
        for (i = 0; i < SIZE; i++)
        {
            for (int k = 0; k < 1000000; k++)
                ; //delay
            c[i] = a[i] + b[i];
        }
        t_end = omp_get_wtime();
    }
    printf("Execution time = %d\n", (t_end - t_ref));
    return 0;
}