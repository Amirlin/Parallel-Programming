#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);               /* starts MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */
    if (rank % 2 == 0)
    {
        printf("I am process %d, my rank is even\n", rank);
    }
    else if (rank % 2 == 1)
    {
        printf("I am process %d, my rank is odd\n", rank);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* get number of processes */
    MPI_Finalize();
    return 0;
}