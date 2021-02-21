#include <stdio.h>
#include <omp.h>
int main()
{
    int i, tid;
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
#pragma omp for
        for (i = 0; i < 20; i++)
        {
            printf("Thread nb %d execute index=%d \n", tid, i);
        }
    }
    return 0;
}