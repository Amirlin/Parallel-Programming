#include <stdio.h>
#include <math.h>
#include <omp.h>
#define nbsteps 1000

int main()
{
    double pi, term;
    double sum = 0.;
    double step = 1. / (double)nbsteps;
    double t_ref, t_end;
    int tid;

#pragma omp parallel
    {
        t_ref = omp_get_wtime();
        tid = omp_get_thread_num();
        printf("Thread %d started... \n", tid);

#pragma omp for schedule(static) reduction(+ \
                                           : sum)
        for (size_t i = 0; i < nbsteps; i++)
        {
            term = (i + 0.2) * step;

            // #pragma omp atomic
            sum += 2. / (1. + term * term);
        }

        t_end = omp_get_wtime();
    }
    pi = step * sum;
    printf("ex time -> %f\npi -> %f\n", t_end - t_ref, pi);

    return 0;
}