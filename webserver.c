#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<errno.h> 
#include <unistd.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in  create_container(int PORT) {
	struct sockaddr_in address;
	memset((char*)&address,
		   0,
		   sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	return address;
}

int main(int argc, char* argv[]){
	const int PORT = 8080;
	const int buffer_size = 1024;
	struct sockaddr_in address = create_container(PORT);
	int addrlen = sizeof(address);
	char buffer[buffer_size]; //buffer to store data that is read from socket
	memset(buffer,
		   0,
		   buffer_size);
	char* message = "Hello from server\n";
	int sckt = socket(AF_INET,		//create the socket
					  SOCK_STREAM,
					  0); 
	if (sckt < 0) {
		perror("cannot open socket\n");
		exit(EXIT_FAILURE);
	}
	int bd = bind(sckt,						//bind the socket to the given port number
				 (struct sockaddr *)&address,
				  sizeof(address)); 
	if (bd < 0) {
		perror("cannot bind the socket\n");
		exit(EXIT_FAILURE);
	}
	int lst = listen(sckt, 3);	//wait for connections 
	if (lst < 0) {
		perror("error in listen\n");
		exit(EXIT_FAILURE);
	}
	for(;;) {
		printf("%s\n\n", "Waiting for connection");
		printf("-------------------------------\n\n");
		int new_sockt = accept(sckt,					//accept connection
					    (struct sockaddr *)&address,
					    (socklen_t*)&addrlen);	
		if (new_sockt < 0) {
			perror("In accept\n");
			exit(EXIT_FAILURE);
		}
		int flag_read = read(new_sockt,
							buffer,
							buffer_size);
		if (flag_read < 0) {
			printf("%s\n", "No bytes to be read");
		}
		printf("%s\n", buffer);
		write(new_sockt,
			 message,
			 strlen(message));
	}
	return EXIT_SUCCESS;
}