//standard libraries
#include <stdio.h>
#include <stdlib.h>
//libraries for socket specific work
#include <sys/types.h>
#include <sys/socket.h>//contains API that includes functionality to create socket

#include <netinet/in.h>//for some structures to include address information

int main()
{
	//creating a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	//Basically using socket function of C returns a descriptor(In Unix and related computer operating systems, a file descriptor (FD, less frequently fildes) is an abstract indicator (handle) used to access a file or other input/output resource, such as a pipe or network socket), this will allow us to make feature calls on our socket.
	
	//use man socket on cmd to see its manual
	
	//Therefore, storing the result in integer
	//first parameter: Domain of socket, sice we are making internet socket , we have to use AF_INET(Defined in one of our headers)
	//Second Parameter: type of socket, connection socket: SOCK_STREAM for TCP
	//Last parameter:for protocol defining; since we are using SOCK_STREAM, not our protocol, therfore 0. If we had to use any out protocol, then case would have been different.
	//THIS HAS CREATED A SOCKET,   A NODE IN NETWORK, ONE SIDE OF CONNECTION.
	//We need to specify address, port details to connect to, Thats why, we need netinet in header.It contains structure to define few fields on so we can connect to remote sockets.
	/*AF_INET:
 	   AF = Address Family
    	PF = Protocol Family

	Meaning, AF_INET refers to addresses from the internet, IP addresses specifically. PF_INET refers to anything in the protocol, usually sockets/ports.
	SOCK_STREAM:
	TCP almost always uses SOCK_STREAM and UDP uses SOCK_DGRAM.
	TCP/SOCK_STREAM is a connection-based protocol. The connection is established and the two parties have a conversation until the connection is terminated by one of the parties or by a network error.
	UDP/SOCK_DGRAM is a datagram-based protocol. You send one datagram and get one reply and then the connection terminates.
	If you send multiple packets, TCP promises to deliver them in order. UDP does not, so the receiver needs to check them, if the order matters.
	If a TCP packet is lost, the sender can tell. Not so for UDP.
	UDP datagrams are limited in size, from memory I think it is 512 bytes. TCP can send much bigger lumps than that.
	TCP is a bit more robust and makes more checks. UDP is a shade lighter weight (less computer and network stress).*/
 


	//specify address for socket
	struct sockaddr_in server_address;//this sockaddr_in is defined in netinet/in.h to specify addresses, here we need to define one address to connect to.
	server_address.sin_family = AF_INET;//sets family of address.
	server_address.sin_port = htons(9002);//sets port. Here we could pass 9001 as port as integer but the data format is different, hence htons is a conversion function and it is included in one of our headers.9002(our port here) should not be being used by the OS.
	server_address.sin_addr.s_addr = INADDR_ANY;//here we are specifying the actual address where we want the socket to connect to, here we are connecting to an ip of the local computer.	//sin_addr is itself an struct .,  INNR_ADDR is default as 0.0.0.0. WIth this, we define where we need to connect to.
//http://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf


	//calling connect function, first parameter is netowrk_socket(the socket of client), 2nd parameter is server address but cast to a different structure type, third is size simply.
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	//connect returns integer, 0 if everything seems OK, -1 if things go wrong.
	if(connection_status == -1)printf("There was an error making a connection to the remote socket \n\n");
	//now we either send or receive data, lets receive data here
	char server_response[256]; //to receive data in form of string

	//recv function receives the data, first parameter:our socket, second:address of variable server_response,third:self explanatory,fourth:some optional flag parameter
	recv(network_socket, &server_response, sizeof(server_response), 0);
	
	//now we print whatever data we received.
	printf("The server sent the data: %s", server_response);
	//now we close the socket
	close(network_socket);
	return 0; 
}
