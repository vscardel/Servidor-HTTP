#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h> 
#include <unistd.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[]){

	const int PORT = 8080;
	const int buffer_size = 1024;

	//generic container to pass to the bind function
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	memset((char*)&address,0,sizeof(address));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	//create the socket
	int sckt = socket(AF_INET,SOCK_STREAM,0);

	if(sckt < 0){
		perror("cannot open socket\n");
		exit(EXIT_FAILURE);
	}

	//bind the socket to the given port number

	int bd = bind(sckt,(struct sockaddr *)&address,sizeof(address));

	if(bd < 0){
		perror("cannot bind the socket\n");
		exit(EXIT_FAILURE);
	}

	//wait for connections 
	int lst = listen(sckt,3);

	if(lst < 0){
		perror("error in listen\n");
		exit(EXIT_FAILURE);
	}

	//buffer to store data that is read from socket
	char buffer[buffer_size];
	memset(buffer,0,buffer_size);
	//message to be sent to client
	char *message = "Hello from server\n";

	while(1){

		printf("%s\n\n","Waiting for connection");
		printf("-------------------------------\n\n");

		//accept connection
		int new_sockt = accept(sckt,(struct sockaddr *)&address,(socklen_t*)&addrlen);

		if(new_sockt < 0){
			perror("In accept\n");
			exit(EXIT_FAILURE);
		}

		int flag_read = read(new_sockt,buffer,buffer_size);

		if(flag_read < 0){
			printf("%s\n","No bytes to be read");
		}

		printf("%s\n",buffer);
		write(new_sockt,message,strlen(message));
	}
	return 0;
}