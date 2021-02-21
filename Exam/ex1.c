#include <stdio.h>
#include <omp.h>
#define N 20
int main()
{
    int array[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int tid, var = 5;
#pragma omp parallel
    {
        tid = omp_get_thread_num();
        printf("Thread %d: started... \n", tid);
#pragma omp for schedule(static, 5)
        for (int i = 0; i < N; i++)
        {
            if (array[i] == var)
            {
                printf("var is founded\n");
#pragma omp cancel for
            }
        }
    }
}