#include <stdio.h>
#include <omp.h>
int main()
{
    printf("Print # 1\n");
#pragma omp parallel num_threads(4)
    {
        printf("Print #2\n");
#pragma omp for
        for (int i = 0; i < 100; i++)
        {
            printf("Print #3 i=%d\n", i);
        }
#pragma omp single
        printf("Print #4\n");
    }
    return 0;
}
