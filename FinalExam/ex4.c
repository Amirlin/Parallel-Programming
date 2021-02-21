#include <stdio.h>
#include <mpi.h>
#include <string.h>
#define size 100
/*
Process 2 sends a welcome message to process 0 and 1.
Process 2 receives the two integer numbers from process 0 and process 1,
after receiving the two numbers process 2 computes and displays the sum.
*/
void main(int argc, char *argv[])
{
    int myrank, nprocs, tag = 100;
    // MPI_Status status;
    int a, s1, s2;
    char msg[size];
    MPI_Request requestR;
    MPI_Request requestS;
    MPI_Status status[1];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    a = myrank;
    if (myrank == 0)
    {

        MPI_Issend(&a, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &requestS);
        MPI_Irecv(msg, size, MPI_CHAR, 2, tag, MPI_COMM_WORLD, &requestR);
        MPI_Wait(&requestR, status);

        printf("Message=%s\n", msg);
    }
    else if (myrank == 1)
    {
        MPI_Issend(&a, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &requestS);
        MPI_Irecv(msg, size, MPI_CHAR, 2, tag, MPI_COMM_WORLD, &requestR);
        MPI_Wait(&requestR, status);

        printf("Message=%s\n", msg);
    }
    else if (myrank == 2)
    {
        strcpy(msg, "Hello");
        MPI_Issend(msg, strlen(msg), MPI_CHAR, 0, tag, MPI_COMM_WORLD, &requestS);
        MPI_Issend(msg, strlen(msg), MPI_CHAR, 1, tag, MPI_COMM_WORLD, &requestS);
        MPI_Irecv(&s1, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &requestR);
        MPI_Irecv(&s2, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &requestR);
        MPI_Wait(&requestR, status);

        printf("Sum=%d\n", (s1 + s2));
    }
    MPI_Finalize();
}