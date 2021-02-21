#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#define n 100000
int main(int argc, char **argv)

{
    int rank, size, code, tag = 100;
    double start, finish, time;
    MPI_Status status;

    float buffer[n];
    MPI_Init(&argc, &argv);               /* starts MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */

    if (rank == 0) //ping process
    {
        for (int i = 0; i < n; i++)
            buffer[i] = i;
        start = MPI_Wtime();
        for (int i = 0; i < 1000; i++)
        {
            MPI_Send(buffer, n, MPI_FLOAT, 1, tag, MPI_COMM_WORLD);
            code = MPI_Recv(buffer, n, MPI_FLOAT, 1, tag, MPI_COMM_WORLD, &status);
        }
        finish = MPI_Wtime();
        time = finish - start;
        printf("Time=%f\n", time);
    }
    else if (rank == 1)
    {
        for (int i = 0; i < 1000; i++)
        {

            code = MPI_Recv(buffer, n, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &status);
            MPI_Send(buffer, n, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}