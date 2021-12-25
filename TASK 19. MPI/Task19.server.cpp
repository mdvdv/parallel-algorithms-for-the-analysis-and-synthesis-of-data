#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);

	char port_name[MPI_MAX_PORT_NAME];
	char client_message[12];
	char server_message[12] = "I am server";

	MPI_Status status;
	MPI_Comm intercomm;

	MPI_Open_port(MPI_INFO_NULL, port_name);

	cout << "Port: " << port_name << endl;
	cout << "Waiting for the client ..." << endl;
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	cout << "Client connected: " << port_name << endl;

	MPI_Recv(client_message, 12, MPI_CHAR, 0, 0, intercomm, &status);
	cout << "Server got message: " << client_message << endl;

	MPI_Send(server_message, 12, MPI_CHAR, 0, 0, intercomm);
	cout << "Server sent message: " << server_message << endl;

	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);

	MPI_Finalize();
	return 0;
}