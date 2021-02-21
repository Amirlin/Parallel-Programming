/*
Write an MPI program that allows a processor to communicate its rank around a ring. The sum
of all ranks is then accumulated and printed out by each processor.
*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int prev, next, rank, size, sum = 0;
    int sBuf, rBuf;
    int tag = 100;
    double t1, t2;

    MPI_Request requestR;
    MPI_Request requestS;
    MPI_Status status[1];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get current process id
    MPI_Comm_size(MPI_COMM_WORLD, &size); //get number of processes
    t1 = MPI_Wtime();
    //identify ranks of neighbours
    sBuf = rank; //send current rank to neighbour

    prev = rank - 1;
    if (prev < 0)
    {
        prev = prev + size;
    }
    next = (rank + 1) % size;

    for (int i = 0; i < size; i++)
    {
        //recieve from prev
        MPI_Irecv(&rBuf, 1, MPI_INT, prev, tag, MPI_COMM_WORLD, &requestR);
        //send to next
        MPI_Issend(&sBuf, 1, MPI_INT, next, tag, MPI_COMM_WORLD, &requestS);

        //wait receive to complete, then use rBuf to sum
        MPI_Wait(&requestR, status);
        sum = sum + rBuf;
        MPI_Wait(&requestS, status);
        sBuf = rBuf;
    }
    printf("proc %d has sum = %d\n", rank, sum);
    t2 = MPI_Wtime();
    MPI_Finalize();
    printf("MPI_Wtime measured : %f\n", t2 - t1);
    return 0;
}