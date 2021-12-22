#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int rank, size, sub_size;
    double start_time;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    int N = 1000000;
    int* array;
    int* sub_array;
    
    if (rank == 0)
    {
	array = new int[N];
	for (int i = 0; i < N; i++)
	{
	    array[i] = 1;
	}
	
	sub_size = N / size;
    }

    MPI_Bcast(&sub_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    sub_array = new int[sub_size]();
    MPI_Scatter(array, sub_size, MPI_INT, sub_array, sub_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_amount = 0;
    for (int i = 0; i < sub_size; i++)
    {
	local_amount += sub_array[i];
    }

    cout << "Process: "<< rank << " Result: " << local_amount << endl;

    start_time = MPI_Wtime();
    int global_amount = 0;
    MPI_Reduce(&local_amount, &global_amount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
    {
        cout << "Result: "<< global_amount << " Time: " << MPI_Wtime() - start_time << endl;
    }
    
    MPI_Finalize();
}