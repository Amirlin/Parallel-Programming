#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#define n 10

int main(int argc, char *argv[])
{
    int tab[n];
    int s0 = 0, s1 = 0, sum;
    omp_lock_t lock;
    float time1, time2;
    omp_init_lock(&lock);

#pragma omp parallel sections shared(tab, s0, s1, sum) num_threads(4)
    {

#pragma omp section
        {
            omp_set_lock(&lock);
            for (int i = 0; i < n; i++)
                tab[i] = i; //rand()%n;
            omp_unset_lock(&lock);
        }

#pragma omp section
        {
            omp_set_lock(&lock);

            for (int i = 0; i < n / 2; i++)
                s0 = s0 + tab[i];
            omp_unset_lock(&lock);
        }
#pragma omp section
        {
            omp_set_lock(&lock);

            for (int i = n / 2; i < n; i++)
                s1 = s1 + tab[i];
            omp_unset_lock(&lock);
        }

#pragma omp section
        {
            omp_set_lock(&lock);
            sum = s0 + s1;
            printf("Sum=%d\n", sum);
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);
}

/*

When running the program with one thread we
obtain:

>Sum=45

Question 1: When running the program with many threads we obtain an incorrect answer,

explain why.

Question 2: Modify the program by using locks only in order to obtain a correct execution.

Please upload the code one Moodle.
*/