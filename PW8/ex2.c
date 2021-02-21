#include <stdio.h>
#include <mpi.h>
/*
Re-Write the parallel program that computes the max of elements in an array by using MPI_Reduce.
*/

int largest(int arr[], int n)
{
    int i;

    // Initialize maximum element
    int max = arr[0];

    // Traverse array elements from second and
    // compare every element with current max
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}
int main(int argc, char **argv)
{
    int max, GlobMax, first, len = 100;
    int rank, size;
    int arr[len];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); //get number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get current process id
    first = len * rank;
    //initialize array
    for (int i = 0; i < len; i++)
    {
        arr[i] = first + i;
    }
    //maximum for each process
    max = largest(arr, len);
    printf("p%d  max = %d\n", rank, max);
    //Global maximum
    MPI_Reduce(&max, &GlobMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("\nMPI_Reduce the Global Max %d\n", GlobMax);
    }
    MPI_Finalize();
    return 0;
}