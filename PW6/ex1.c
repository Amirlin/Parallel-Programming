/*
Write an MPI program with two processes in such a way that the process 0 reads an integer
number using scanf. Process 0 sends the number to process 1, which calculates the factorial of
the number and returns the results to process 0.
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int rank, size, n, rn, code, fact = 1, tag = 100;
    MPI_Init(&argc, &argv);               /* starts MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */
    /*
int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
Sending, from the address buf, a message of count elements of type
datatype, tagged tag, to the process of rank dest in the communicator
comm.
    */
    if (rank == 0)
    {
        printf("enter number : \n");
        scanf("%d", &n);
        code = MPI_Send(&n, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
        printf("input %d sended from p0 to p1\n", n);
    }
    else if (rank == 1)
    {
        code = MPI_Recv(&rn, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("p1 has received the %d from p0.\n", rn);
        for (int i = 1; i <= rn; i++)
        {
            fact = fact * i;
        }
        printf("Factorial of %d is %d\n", rn, fact);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* get number of processes */

    MPI_Finalize();
    return 0;
}