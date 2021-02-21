#include <stdio.h>
#include <omp.h>
#define N 20
int main()
{
    int array[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 5, 13, 14, 15, 5, 17, 18, 19, 20};
    int tid, var = 5, count = 0;
#pragma omp parallel
    {
        tid = omp_get_thread_num();
        printf("Thread %d: started... \n", tid);
#pragma omp for schedule(static, 5) reduction(+ \
                                              : count)
        for (int i = 0; i < N; i++)
        {
            if (array[i] == var)
            {
                printf("var is founded\n");
                count++;
#pragma omp cancel for
            }
        }
    }
    printf("count is %d\n", count);
}