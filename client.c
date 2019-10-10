#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h> 
#include <unistd.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){

	const int PORT = 8080;
	const int buffer_size = 1024;
	char * address = "127.0.0.1";


	struct sockaddr_in server_address;
	memset(&server_address,'0',sizeof(server_address));

	int sckt = socket(AF_INET,SOCK_STREAM,0);

	if(sckt < 0){
		perror("on socket\n");
		exit(EXIT_FAILURE);
	}

	server_address.sin_port = htons(PORT);
	server_address.sin_family = AF_INET;

	//inet_pton convert the address of the server to binary form
	int convert = inet_pton(AF_INET,address,&server_address.sin_addr);

	if(convert < 0){
		perror("On convertion\n");
		exit(EXIT_FAILURE);
	}

	//connect to the server
	connect(sckt,(struct sockaddr *)&server_address,sizeof(server_address));

	if(connect < 0){
		perror("On connect\n");
		exit(EXIT_FAILURE);
	}

	//send message to the server
	char *message = "Hello from the client!\n";
	write(sckt,message,strlen(message));
	printf("%s\n","Message sent\n");

	//read response;

	char buffer[buffer_size];
	memset(buffer,0,buffer_size);

	int flag_read = read(sckt,buffer,buffer_size);

	if(flag_read < 0){
		perror("On read\n");
		exit(EXIT_FAILURE);
	}

	printf("%s","Response from server: ");
	printf("%s\n",buffer);

	return 0;
}