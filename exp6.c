//filename: sv.c(exp6)

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
 printf("Server side\n");

//buff used to store message
 char buffer[50];
 int sockfd;

//sockaddr_in structure
 struct sockaddr_in addr;

//Assigning family,ipaddress and port
 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=3008;
 int s=sizeof(struct sockaddr_in);

//Sending data as dgram
 sockfd=socket(AF_INET,SOCK_DGRAM,0);

//binding the socket
 bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
 do
 {
  printf("Connection Established\n");
  printf("Receiving message from client: ");

//receving message from client
  recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&s);
  printf("%s",buffer);
  printf("\nEnter the message:");
  scanf("%s",buffer);

//sending message to client
  sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,s);
  }while(strcmp(buffer,"stop")!=0);
  close(sockfd);
}

//filename: cl.c(exp6)

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
 printf("Client side\n");

//buff to store the message
 char buffer[50];
 int sockfd;
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 struct sockaddr_in addr;

//Assigning the family,ipaddress and port
 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=3008;
 int s=sizeof(struct sockaddr_in);

//connecting to the server
 connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
 do
 {
  printf("Sending message to server: ");
  scanf("%s",buffer);


//sending message to server
  sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,s);

//receiving message from server
  recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&s);
  printf("Received from server:%s\n",buffer);
  }while(strcmp(buffer,"stop")!=0);
  close(sockfd);
}

/*

OUTPUT:

sv.exe

s6cs107@comp49:~$ gcc -o sv sv.c
s6cs107@comp49:~$ ./sv
Server side
Connection Established
Receiving message from client: hi
Enter the message:hello 
Connection Established
Receiving message from client: stop
Enter the message:stop
s6cs107@comp49:~$ 

cl.exe

s6cs107@comp49:~$ gcc -o cl cl.c
s6cs107@comp49:~$ ./cl
Client side
Sending message to server: hi
Received from server:hello
Sending message to server: stop
Received from server:stop
s6cs107@comp49:~$ 


*/
