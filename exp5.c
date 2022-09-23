//filename: server.c(exp5)

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
 printf("Server side\n");
//Creating a buffer for the store the message
 char buffer[50];
 int sockfd,newsocket;

//Creating socket addresses
 struct sockaddr_in addr1,addr2;

//Assigning familytype,ifaddress and port
 addr1.sin_family=AF_INET;
 addr1.sin_addr.s_addr=INADDR_ANY;
 addr1.sin_port=3008;
 int s=sizeof(struct sockaddr_in);
 sockfd=socket(AF_INET,SOCK_STREAM,0);

//binding the socket address
 bind(sockfd,(struct sockaddr *)&addr1,sizeof(addr1));

//listening
 listen(sockfd,5);
//Creating a new socket for client
 newsocket=accept(sockfd,(struct sockaddr *)&addr2,(&s));

//Sending and receiving messages from server and client
 do
 {
  printf("Connection Established\n");
  printf("Receiving message from client: ");
  recv(newsocket,buffer,sizeof(buffer),0);
  printf("%s",buffer);
  printf("\nEnter the message:");
  scanf("%s",buffer);
  send(newsocket,buffer,sizeof(buffer),0);
  }while(strcmp(buffer,"stop")!=0);

//Closing the open sockets
  close(newsocket);
  close(sockfd);
}

//filename: client.c(exp5)

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
 printf("Client side\n");
 char buffer[50];
 int sockfd;

//Creating a socket for communication
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 struct sockaddr_in addr1,addr2;

//Assigning family,ipaddress and port
 addr2.sin_family=AF_INET;
 addr2.sin_addr.s_addr=INADDR_ANY;
 addr2.sin_port=3008;

//connecting to the server
 connect(sockfd,(struct sockaddr *)&addr2,sizeof(addr2));

//Sending and receiving message from client and server
 do
 {
  printf("Sending message to server: ");
  scanf("%s",buffer);
  send(sockfd,buffer,sizeof(buffer),0);
  recv(sockfd,buffer,sizeof(buffer),0);
  printf("Received from server:%s\n",buffer);
  }while(strcmp(buffer,"stop")!=0);

//closing the open sockets
  close(sockfd);
}


/*

OUTPUT:

server.exe

s6cs107@comp49:~$ gcc -o server server.c
s6cs107@comp49:~$ ./server
Server side
Connection Established
Receiving message from client: hello
Enter the message:hi
Connection Established
Receiving message from client: stop
Enter the message:stop
s6cs107@comp49:~$ 

client.exe

s6cs107@comp49:~$ gcc -o client client.c
s6cs107@comp49:~$ ./client
Client side
Sending message to server: hello
Received from server:hi
Sending message to server: stop
Received from server:stop
s6cs107@comp49:~$ 


*/
