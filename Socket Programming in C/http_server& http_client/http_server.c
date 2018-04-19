#include <stdio.h>
#include <stdlib.h>
#include <string.h>//since here we need to manipulate strings

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
int main()
{
        //We are going to need to get data of file we will be using as http file and return it as html
        FILE *html_data;
        html_data = fopen("index.html", "r");//we want to read from the file.

        char response_data[1024];
        fgets(response_data, 1024, html_data);
        //so far we have opened the html file and read it into our applpication

        char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
        //we want to concatenate http_header with actual file data we will be serving
        strcat(http_header, response_data);

        //http server just assigns a specific type of content, rest remains same
	printf("%s", http_header);
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);

        //define the address
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(8001);
        server_address.sin_addr.s_addr = INADDR_ANY;

        //bind it
        bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

        listen(server_socket, 5);

        int client_socket;
        //now we are going to wrap in while loop because we want the server to keep responding
        while(1){
                client_socket = accept(server_socket, NULL, NULL);
                send(client_socket, http_header, sizeof(http_header), 0);
                close(client_socket);
        }
        return 0;
}
