#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main()
{
	//response message
	char server_message[256]="\n \n You have reached the server!";
	int server_socket;
	//creating server socket in the same way
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to our specified IP and port
	
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 5);//5 is number of connections it has to listen to at max
	//when the server_socket starts listening to the client, we need to start accepting the client socket so that we can write to it( the whole idea).
	//An integer holds the client_socket
	
	int client_socket;
	//in the next line, we are able to get the client_socket that allows us to manipulate things on the client side.
	client_socket = accept(server_socket, NULL, NULL);//now we have client socket
	//first parameter is the socket on which server is listening, second and third are struct that contain address from where the client is connecting from and its size, nutsince we are doing it in local machine, we are not interested in it.
	//the two NULL parameters contain info about where the request is coming from , important in general for servers to reply to request. But here we are connecting to the same machine and same ports and everything, its OK to put NULL
	//After this(the line above), we have created a 2 way connection.
	

	send(client_socket, server_message, sizeof(server_message), 0);
			//first parameter is socket to which we are sending data to and second parameter is what data we are sending.
	
	//closing the connection
	close(server_socket);
	return 0;
}
