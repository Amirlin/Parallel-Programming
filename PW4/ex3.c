#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    omp_lock_t lock;
    float time1, time2;
    omp_init_lock(&lock);
    int p;
    time1 = omp_get_wtime();
#pragma omp parallel sections num_threads(2)
    // default(none)
    {
#pragma omp section
        {
            omp_set_lock(&lock);
            p = omp_get_thread_num();
            printf("Th%d: Hello\n", p);
            omp_unset_lock(&lock);
        }
#pragma omp section
        {
            omp_set_lock(&lock);
            p = omp_get_thread_num();
            printf("Th%d: World\n", p);
            omp_unset_lock(&lock);
        }
#pragma omp section
        {
            omp_set_lock(&lock);
            p = omp_get_thread_num();
            printf("Th%d: Bye\n", p);
            omp_unset_lock(&lock);
        }
    }
    time2 = omp_get_wtime();
    printf("execution time=%f\n", (time2 -
                                   time1));
    omp_destroy_lock(&lock);
    return 0;
}