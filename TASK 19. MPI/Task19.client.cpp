#include <iostream>
#include <mpi.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    char port_name[MPI_MAX_PORT_NAME];
    char client_message[12] = "I am client";
    char server_message[12];

    MPI_Status status;
    MPI_Comm intercomm;
    strcpy(port_name, argv[1]);

    cout << "Attempt to connect ..." << endl;
    MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
    cout << "Server connection: " << port_name << endl;

    MPI_Send(&client_message, 12, MPI_CHAR, 0, 0, intercomm);
    cout << "Client sent message: " << client_message << endl;

    MPI_Recv(server_message, 12, MPI_CHAR, 0, 0, intercomm, &status);
    cout << "Client got message: " << server_message << endl;

    MPI_Finalize();
    return 0;
}