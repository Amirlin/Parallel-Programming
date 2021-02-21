/*
Consider that we have n processes, modify the program in order to distribute the calculation over all
available processes and measure the gain in execution time compared to exercise 2.
*/
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <time.h>
#define N 10
int main(int argc, char **argv)
{
    int rank, size, b, code, tag = 100, numbers_per_rank;
    int my_array[N];
    int recieve[N];
    int first, last;
    for (int i = 0; i < N; i++)
    {
        my_array[i] = i;
    }
    MPI_Init(&argc, &argv); /* starts MPI */
    double t1 = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* get number of processes */
    numbers_per_rank = floor(N / size);
    if (N % size > 0)
    {
        // Add 1 in case the number of ranks doesn't divide the number of numbers
        numbers_per_rank += 1;
    }

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            code = MPI_Send(my_array, N, MPI_INTEGER, i, tag, MPI_COMM_WORLD);
            printf("Array sended from p%d to p%d\n", rank, i);
        }
    }
    else
    {
        code = MPI_Recv(recieve, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("Process %d, has received the array from process 0.\n", rank);
        // Figure out the first and the last iteration for this rank
        first = rank * numbers_per_rank;
        last = first + numbers_per_rank;
        // Run only the part of the loop this rank needs to run
        // The if statement makes sure we don't go over
        for (int i = first; i < last; i++)
        {
            if (i < N)
            {
                // printf("I'm rank %d and I'm printing the number %d.\n", rank, i);
                int temp = recieve[i], fact = 1;
                //find factorial
                for (int ii = 1; ii <= temp; ii++)
                {
                    fact = fact * ii;
                }
                printf("Recived array[%d] = %d ,Factorial of %d = %d\n", i, recieve[i], recieve[i], fact);
            }
        }
    }
    double t2 = MPI_Wtime();
    printf("MPI_Wtime measured : %f\n", t2 - t1);

    MPI_Finalize();
    return 0;
}