//filename: (server)exp7

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>

int main()
{
 	printf("Server side\n");


 	char buffer[50];
 	int sockfd=socket(AF_INET,SOCK_DGRAM,0);


 	struct sockaddr_in addr;

 	addr.sin_family=AF_INET;
 	addr.sin_addr.s_addr=INADDR_ANY;
 	addr.sin_port=5555;

 	bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
 
while(1){
  
 	int s;
 	recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&s);
 
 	if(fork() == 0){
 	time_t t = time(0);
 	sprintf(buffer,"\n time is %s", ctime(&t));
 	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,sizeof(addr));
}
}
 	close(sockfd);
	return 0;

}

//filename: (client)exp7

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>

int main()
{
 	printf("Client side\n");
 
 	int s;
 	char buffer[50] = "hello";
 	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
 
 	struct sockaddr_in addr; 
 	addr.sin_family=AF_INET;
 	addr.sin_addr.s_addr=INADDR_ANY;
 	addr.sin_port=5555;

  
  	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,sizeof(addr));
  	recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&s);
  	printf("Received from server:%s\n",buffer);
  
  
 	close(sockfd);
  	return 0;
  
}

/*

OUTPUT:

s6cs107@comp49:~$ gcc -o svt svt.c
s6cs107@comp49:~$ ./svt
Server side

s6cs107@comp49:~$ gcc -o cl2 cl.c
s6cs107@comp49:~$ gcc -o cl1 cl.c
s6cs107@comp49:~$ ./cl1 && ./cl2
Client side
Received from server:
 time is Fri Jun 10 11:50:33 2022

Client side
Received from server:
 time is Fri Jun 10 11:50:33 2022


*/
