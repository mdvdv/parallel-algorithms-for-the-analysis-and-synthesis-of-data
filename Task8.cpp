#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank;
    double start_time, time;
    int length = 1;
    int count, array[1000000];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Status status;
    
    if (rank == 0)
    {
	while (length < 1000000)
	{
    	    start_time = MPI_Wtime();
	    for (int i = 0; i < 10000; i++)
	    {
		MPI_Send(&array, length, MPI_INT, 1, 5, MPI_COMM_WORLD);
		MPI_Recv(&array, length, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
	    }
	    
	    time = MPI_Wtime() - start_time;
	    cout << "Message Size: " << length * 0.000001 * sizeof(int) << endl;
	    length *= 10;
	}
	
	start_time = MPI_Wtime();
	for (int i = 0; i < 10000; i++)
	{
	    MPI_Send(&array, 0, MPI_INT, 1, 5, MPI_COMM_WORLD);
	    MPI_Recv(&array, 0, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
	}
	
	time = MPI_Wtime() - start_time;
	cout << "Latency: " << time / 2 << endl;
    	MPI_Send(&rank, 1, MPI_INT, 1, 15, MPI_COMM_WORLD);
    }
    
    if (rank == 1)
    {
	while (true)
	{
	    MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	    if (status.MPI_TAG == 15)
	    {
		break;
	    }
	    
	    MPI_Get_count(&status, MPI_INT, &count);
	    MPI_Recv(&array, count, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
	    MPI_Send(&array, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
	}
    }

    MPI_Finalize();
}