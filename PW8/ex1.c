#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
/*
write a parallel MPI program that computes the maximum of elements in an array. The process 0
initializes the array with random numbers.

The array is distributed using MPI_Scatter.
Each process computes a local max.
Results are collected by process 0 using MPI_Gather.
Process 0 computes and displays the global max.*/

#define N 100

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

int main(int argc, char *argv[])
{
    int rank, size, block_length, i = 0, localMax = 0;
    static int max = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); //number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //current process id

    block_length = N / size;

    int *initData = (int *)malloc(N * sizeof(int));
    int *data = (int *)malloc(block_length * sizeof(int));
    int *arr = (int *)malloc(size * sizeof(int));

    for (i = 0; i < N; i++)
        initData[i] = i;
    //array is distributed
    MPI_Scatter(initData, block_length, MPI_INT, data, block_length, MPI_INT, 0, MPI_COMM_WORLD);

    //computing the local max of each process
    for (i = 0; i < block_length; i++)
        localMax = data[(largest(data, size))];
    printf("procces %d local Max= %d\n", rank, localMax);

    // MPI_Gather process 0
    MPI_Gather(&localMax, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        max = largest(arr, size);
        printf("\nGlobal Max = %d\n", max);
    }
    MPI_Finalize();
    return 0;
}