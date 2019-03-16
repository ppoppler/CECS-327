/**
 * Rayhaan Shaikh
 * Philip Poppler
 * This program demonstrates setting up a client and server that send and receieve messages with each other.
 * The objective is to learn socket programming in C.
 * */
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <fcntl.h>
#define PORT 8080 
/**
 * the main method contains code to set up the server so it can send and receive messages with the client it connects to
 * */
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; //this structure is used for handling internet addresses. This struct consists of an address family,port in network byte order, and an internet address.
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creates a socket file descriptror 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) //if the returned result equals 0, print an error message 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	//attaches the socket to port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; //sin_family contains code for the address family
	address.sin_addr.s_addr = INADDR_ANY; //sin_addr is the ip address in the socket
	address.sin_port = htons( PORT ); //htons is used to convert values between host and network byte orders

	//attaches the socket to the port 8080, forecefully 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) //the listen function is used to listen for socket connections
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) //the accept function is used to accept a new connection on a socket
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Connected! \n"); //if we have successfully all the lines of code needed for the setup of the server, print out that a connection has been made
	while(1){ //loop forever 
		
	valread = read( new_socket , buffer, 1024); //read is used to read data into a buffer
	
	printf("Client: ");
	printf("%s\n",buffer ); //print out the message that was received from the client
	char msg[1024];//used for holding the message 
	 
	fgets(msg,1024,stdin);//user input for the message 
	send(new_socket , msg , strlen(msg) , 0 ); //the send function only sends a message when the socket is connected, it is used to send a message on a socket

	fseek(stdin,0,SEEK_END);//fseek is used to move the file pointer that is associated with a given file to a specified position, the parameters are a stream, offset, and whence
	memset(&msg,'\0',sizeof(msg)); //used for clearing the char array
	memset(&buffer,'\0',sizeof(buffer));//used for clearing the buffer 
	}
	return 0; 
} 
