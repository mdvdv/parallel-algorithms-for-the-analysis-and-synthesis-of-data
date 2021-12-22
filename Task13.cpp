#include <iostream>
#include <mpi.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    
    int rank, size;
    double start_time, time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int** a = new int* [n];
    int** b = new int* [n];
    int** c = new int* [n];
    
    for (int i = 0; i < n; i++)
    {
	a[i] = new int[m];
	b[i] = new int[m];
	c[i] = new int[m];
	
	for (int j = 0; j < m; j++)
	{
	    a[i][j] = (double(rand()) / RAND_MAX);
	    b[i][j] = (double(rand()) / RAND_MAX);
	}
    }

    MPI_Barrier(MPI_COMM_WORLD);

    start_time = MPI_Wtime();
    for (int i = 0; i < n; i++)
    {
	for (int j = 0; j < m; j++)
	{
	    c[i][j] = 0;

	    for (int k = 0; k < m; k++)
	    {
		c[i][j] = c[i][j] + a[i][k] * b[k][j];
	    }
	}
    }

    time = (double)(MPI_Wtime() - start_time);
    cout << "Process: " << rank << " Execution Time: " << time << endl;

    MPI_Finalize();
}