#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <time.h>
#define N 1000
int main(int argc, char **argv)
{
    int rank, size, b, code, tag = 100;
    float my_array[N];
    float recieve[N];
    srand(time(NULL));
    int i;
    for (i = 0; i < N; i++)
    {
        my_array[i] = rand();
    }
    MPI_Init(&argc, &argv); /* starts MPI */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */
    if (rank == 0)
    {
        code = MPI_Send(my_array, N, MPI_FLOAT, 1, tag, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        code = MPI_Recv(recieve, N, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("Process 1, has received the array from process 0.\n");

        for (int i = 0; i < N; i++)
        {
            printf("array[%d]=%f.\n", i, recieve[i]);
        }
    }
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* get number of processes */

    MPI_Finalize();
    return 0;
}