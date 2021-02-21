#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char **argv)
{
    int my_id, root_process, ierr, num_procs = 4, value;
    MPI_Status status;

    /* Create child processes, each of which has its own variables.
       * From this point on, every process executes a separate copy
       * of this program.  Each process has a different process ID,
       * ranging from 0 to num_procs minus 1, and COPIES of all
       * variables defined in the program. No variables are shared.
       **/

    ierr = MPI_Init(&argc, &argv);

    /* find out MY process ID, and how many processes were started. */

    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    for (an_id = 1; an_id < num_procs; an_id++)
    {
        value = rand();
        ierr = MPI_Send(&value, 1, MPI_INT,
                        an_id, send_data_tag, MPI_COMM_WORLD);
    }

    /* and, then collect the results from the slave processes,
    * here in a variable called array2, and do something with them. */

    for (an_id = 1 an_id < num_procs; an_id++)
    {

        ierr = MPI_Recv(&value1, 1, MPI_FLOAT,
                        MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        /* do something with array2 here */
    }

    if (my_id == 0)
    {

        printf("My id is %d\n", my_id);
    }
    else if (my_id == 1)
    {

        printf("My id is %d\n", my_id);
    }
    else if (my_id == 2)
    {

        printf("My id is %d\n", my_id);
    }
    else
    {

        printf("nothing\n");
    }
    /* Stop this process */

    ierr = MPI_Finalize();
}
/* distribute portions of array1 to slaves. */
