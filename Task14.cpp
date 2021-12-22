#include <iostream>
#include <mpi.h>

#define n 1000

using namespace std;

void suprem(void *a, void *b, int *l, MPI_Datatype *type)
{
    for (int i = 0; i < *l; i++)
    {
	((int*)b)[i] = max(((int*)a)[i], ((int*)b)[i]);
    }
}

int main(int argc, char** argv)
{
    int rank, size, i;
    int a[n];
    int out_1[n];
    int out_2[n];

    MPI_Init(&argc, &argv);
    MPI_Op op;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for (i = 0; i < n; i++) a[i] = i + rank + 1;
    {
	cout << "Process: " << rank << " a[0]: " << a[0] << endl;
    }
    
    MPI_Op_create(&suprem, 1, &op);
    MPI_Reduce(a, out_1, n, MPI_INT, op , 0, MPI_COMM_WORLD);
    MPI_Op_free(&op);
    if (rank == 0)
    {
	cout << "My Result: " << out_1[0] << endl;
    }

    MPI_Reduce(a, out_2, n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
	cout << "MPI Result " << out_2[0] << endl;
    }

	MPI_Finalize();
}