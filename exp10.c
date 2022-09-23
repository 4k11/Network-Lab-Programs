//filename: smtp[server] (exp 10)

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>


void main(){

	printf("server side\n");
	
	char from[50];
	char to[50];
	char subject[50];
	char message[50];
	int sockfd, newsocket;
	
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY;
	addr.sin_port=4348;
	
	int s=sizeof(struct sockaddr_in);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	
	listen(sockfd, 5);
	
	newsocket = accept(sockfd, (struct sockaddr *)&addr, (&s));
	
 do
 {
  printf("\nConnection Established\n");
  printf("Receiving message from client: ");
  recv(newsocket,from,sizeof(from),0);
  recv(newsocket,to,sizeof(to),0);
  recv(newsocket,subject,sizeof(subject),0);
  recv(newsocket,message,sizeof(message),0);
  
  printf("\nfrom: \n");
  printf("%s",from);
  printf("\nto: \n");
  printf("%s",to);
  printf("\nsubject: \n");
  printf("%s",subject);
  printf("\nmessage: \n");
  printf("%s",message);
  
  printf("\nFROM DOMAIN: \n");

  for(int i =0 ;from[i]!='\0';i++){
  if(from[i] == '@'){ 
	for(int j = i+1;from[j]!='.';j++)
  	printf("%c",from[j]);
  	break;
  }
  }
  
  printf("\nTO DOMAIN: \n");
  
  for(int i =0 ;to[i]!='\0';i++){
  if(to[i] == '@'){ 
	for(int j = i+1;to[j]!='.';j++)
  	printf("%c",to[j]);
  	break;
  }
  }
  
  break;
  }while(1);


  close(newsocket);
  close(sockfd);
}

/*
OUTPUT:

s6cs107@comp49:~$ gcc -o smtps smtps.c
s6cs107@comp49:~$ ./smtps
server side

Connection Established
Receiving message from client: 
from: 
sree@mbcet.ac.in
to: 
akil.dhnx@gmail.com
subject: 
hello sensei
message: 
can you be my master please
FROM DOMAIN: 
mbcet
TO DOMAIN: 
gmail
*/

//filename: smtp[client] (exp 10)

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

void main(){
 printf("Client side\n");
 char from[50];
 char to[50];
 char subject[50];
 char message[50];
 int sockfd;


 sockfd=socket(AF_INET,SOCK_STREAM,0);
 struct sockaddr_in addr;


 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=4348;

 connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));

 do
 {
  printf("from: \n");
  scanf("%s",from);
  printf("to: \n");
  scanf("%s",to);
  printf("subject: \n");
  
  getchar();
  gets(subject);
  
  printf("message: \n");

  gets(message);

  send(sockfd,from,sizeof(from),0);
  send(sockfd,to,sizeof(to),0);
  send(sockfd,subject,sizeof(subject),0);
  send(sockfd,message,sizeof(message),0);
  
  break;

  }while(1);


  close(sockfd);
}

/*
OUTPUT:

s6cs107@comp49:~$ gcc -o smtpc smtpc.c
[WARNING FOR GETS MIGHT BE SHOWN]

s6cs107@comp49:~$ ./smtpc
Client side
from: 
sree@mbcet.ac.in
to: 
akil.dhnx@gmail.com
subject: 
hello sensei
message: 
can you be my master please


*/
