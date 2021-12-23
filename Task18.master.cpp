#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank1, rank2, n;
    MPI_Status status;
    MPI_Comm intercomm;

    char slave[17] = "./Task18.slave.o";

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_spawn(slave, MPI_ARGV_NULL, 3, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm, MPI_ERRCODES_IGNORE);
    
    MPI_Recv(&rank1, 1, MPI_INT, 0, 0, intercomm, &status);
    MPI_Recv(&rank2, 1, MPI_INT, 1, 1, intercomm, &status);

    cout << "Slaves: " << rank1 << "; " << rank2 << endl;

    MPI_Recv(&n, 1, MPI_INT, 2, 2, intercomm, &status);

    cout << "Slave: " << status.MPI_SOURCE << " Number of running processes: " << n << endl;

    MPI_Finalize();
    return 0;
}