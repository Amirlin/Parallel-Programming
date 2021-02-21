#include <stdio.h>
#include <omp.h>
#define N 50

int main()
{

    double C[N][N], A[N][N], B[N][N];
    size_t i, j, k;
    int tid;
    double t_ref, t_end, t_exec;

#pragma omp parallel private(tid)
    {

        tid = omp_get_thread_num();
        printf("Thread %d: started... \n", tid);

        t_ref = omp_get_wtime();

#pragma omp for
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                C[i][j] = 0.;
                for (k = 0; k < N; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        t_end = omp_get_wtime();
    }
    t_exec = t_end - t_ref;
    printf("Execution time = %f\n", t_exec);
    return 0;
}
// #include <stdio.h>
// #include <omp.h>
// #include <time.h>
// #define N 50
// int main()
// {
//     clock_t begin = clock();
//     double C[N][N], A[N][N], B[N][N];
//     size_t i, j, k;
//     for (i = 0; i < N; i++)
//     {
//         for (j = 0; j < N; j++)
//         {
//             C[i][j] = 0.;
//             for (k = 0; k < N; k++)
//             {
//                 C[i][j] += A[i][k] * B[k][j];
//             }
//         }
//     }
//     /* here, do your time-consuming job */

//     clock_t end = clock();
//     double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//     printf("ex time: %f\n", time_spent);
// }