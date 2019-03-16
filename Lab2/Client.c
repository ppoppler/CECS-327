/**
 * Rayhaan Shaikh
 * Philip Poppler
 * This program demonstrates setting up a client and server that send and receieve messages with each other.
 * The objective is to learn socket programming in C.
 * */ 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <fcntl.h>
#define PORT 8080 
/**
 * the main method contains code to set up the client so it can send and receive messages with the server it connects to
 * */
int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address;  //this structure is used for handling internet addresses. This struct consists of an address family,port in network byte order, and an internet address.
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; //using this for the server address
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)  //cheking to see if the socket was created properly 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); //memset is used to fill the first x bytes of the memory area that is being pointed to with our constant byte 

	serv_addr.sin_family = AF_INET; //sin_family contains code for the address family
	serv_addr.sin_port = htons(PORT); //htons is used to convert values between host and network byte orders
	
	// This is used to convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) //if the function returns a value <= 0, then throw an error
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 
	//connect() is used to start a connection on a socket
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)  
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}

 
	printf("Connection Established \n"); //print to the console that a connection was successfully established since we were able to successfully 
	printf("IP:127.0.0.1 Port:8080 \n"); //run all of the lines of code above this one to get to here 

	while(1){ //loop forever 
	char msg[1024];//used for holding the message 
	

	fgets(msg,1024,stdin); //used to get user input for the message that the user client enters 
	send(sock , msg , strlen(msg) , 0 ); //the send function only sends a message when the socket is connected, it is used to send a message on a socket
	fseek(stdin,0,SEEK_END); //fseek is used to move the file pointer that is associated with a given file to a specified position, the parameters are a stream, offset, and whence
	valread = read( sock , buffer, 1024); //read is used to read data into a buffer 
	printf("Server: ");
	printf("%s\n",buffer );  //print out the message that was received from the server 
	memset(&msg,'\0',sizeof(msg)); //used for clearing the char array
	memset(&buffer,'\0',sizeof(buffer)); //used for clearing the buffer 
	}
	return 0; 
}
