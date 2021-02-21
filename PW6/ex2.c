/*
Consider that process 0 have an array of integer numbers where we should compute the factorial of all
the elements in the array. Modify the program in order to send the array to process 1 that computes all
the factorials and return the results to process 0.
*/
#include <stdio.h>
#include <mpi.h>
#define N 10
int main(int argc, char **argv)
{
    int rank, size, b, code, tag = 100;
    int my_array[N];
    int recieve[N];
    int newArray[N];
    int i;
    for (i = 0; i < N; i++)
    {
        my_array[i] = i;
    }
    MPI_Init(&argc, &argv); /* starts MPI */
    double t1 = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */
    if (rank == 0)
    {
        code = MPI_Send(my_array, N, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
        printf("Array sended from p0 to p1\n");
        code = MPI_Recv(my_array, N, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("Array recieved from p1 in p0\n");
    }
    else if (rank == 1)
    {
        code = MPI_Recv(recieve, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("Process 1, has received the array from process 0.\n");

        for (int i = 0; i < N; i++)
        {
            int temp = recieve[i], fact = 1;
            //find factorial
            for (int ii = 1; ii <= temp; ii++)
            {
                fact = fact * ii;
            }
            newArray[i] = fact;
            printf("Recived array[%d] = %d ,Factorial of %d = %d\n", i, recieve[i], recieve[i], newArray[i]);
        }
        code = MPI_Send(newArray, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* get number of processes */
    double t2 = MPI_Wtime();
    printf("MPI_Wtime measured : %f\n", t2 - t1);

    MPI_Finalize();
    return 0;
}