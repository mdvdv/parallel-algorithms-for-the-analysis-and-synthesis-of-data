#include <iostream>
#include <mpi.h>

using namespace std;

#define BUFSIZE 100

void filemaker(char* filename)
{
    MPI_File fh;
    MPI_Status status;
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
    MPI_File_write(fh, "I was here!", 12, MPI_CHAR, &status);
    MPI_File_close(&fh);
}

int main(int argc, char **argv)
{
    int bufsize, num, sum;
    char buf[BUFSIZE];
    char filename[] = "file.txt";

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_File fh;

    filemaker(filename);

    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

    sum = 0;

    do
    {
	MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
	MPI_Get_count(&status, MPI_CHAR, &num);
	
	cout << "buf: " << buf << endl;

	sum += num;
    } while (num >= BUFSIZE);

    MPI_File_close(&fh);
    MPI_File_delete(filename, MPI_INFO_NULL);

    cout << "Number of read symbols: " << sum << endl;

    MPI_Finalize();
}