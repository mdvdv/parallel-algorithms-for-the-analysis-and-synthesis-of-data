#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    char *message;
    const int max_length = 1000000;

    for (int length = 1; length <= max_length; length *= 10)
    {
	message = new char[length];
	double start_time = MPI_Wtime();
	for (int i = 0; i < 10; i++)
	{
	    if (rank == 0)
	    {
		MPI_Send(message, length, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(message, length, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
	    }

	    if (rank == 1)
    	    {
		MPI_Recv(message, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Send(message, length, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
	    }
	}
	
	if (rank == 0)
	{
	    double stop = MPI_Wtime();
	    double time = stop - start_time;
	    double bandwidth = 2. * 10 * length / time;
	    double latency = time / (2. * 10);

	    cout << "Latency: " << latency << endl;
	    cout << "Message Size: " << length << " Bandwidth: " << bandwidth / time << " bytes/s" << endl;
	}
    }
    MPI_Finalize();
}