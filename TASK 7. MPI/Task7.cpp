#include <iostream>
#include <mpi.h>

using namespace std;

int dotProduct(int *a, int *b, int n)
{
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        result += a[i] * b[i];
    }
    
    return result;
}

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int a[N], b[N];
    double global_product;
    int sub_size = N / size;
    
    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
	{
	    a[i] = 1;
	    b[i] = 1;
	}
    }
    
    int *sub_a = (int*)malloc(sizeof(int) * sub_size);
    int *sub_b = (int*)malloc(sizeof(int) * sub_size);
    MPI_Scatter(a, sub_size, MPI_INT, sub_a, sub_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, sub_size, MPI_INT, sub_b, sub_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    double local_product;
    local_product = dotProduct(sub_a, sub_b, sub_size);
    MPI_Reduce(&local_product, &global_product, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
    {
	cout << "Dot Product = " << global_product;
    }
    
    MPI_Finalize();
}