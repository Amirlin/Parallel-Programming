#include <stdio.h>
#include <omp.h>
// int main()
// {
//     size_t nb_threads = 0;
// #pragma omp parallel
//     {
//         nb_threads++;
//     }
//     printf("nb_threads = %zu\n", nb_threads);
// }

// first correction
// int main()
// {
//     size_t nb_threads = 0;
// #pragma omp parallel
//     {
// #pragma omp atomic
//         nb_threads++;
//     }
//     printf("nb_threads = %zu\n", nb_threads);
//     return 0;
// }
// second correction

int main()
{
    size_t nb_threads = 0;
#pragma omp parallel
    {
#pragma omp critical(nb_threads)
        nb_threads++;
    }
    printf("nb_threads = %zu\n", nb_threads);
    return 0;
}