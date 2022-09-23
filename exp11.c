//filename: (server)exp11

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
 printf("Server side\n");

 char buffer[50];
 char msg[50];
 int sockfd,newsocket;
 char yo[500];

 struct sockaddr_in addr;

 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=5060;
 int s=sizeof(struct sockaddr_in);
 sockfd=socket(AF_INET,SOCK_STREAM,0);

 bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
 listen(sockfd,5);

 do
 {
  newsocket=accept(sockfd,(struct sockaddr *)&addr,(&s));
  char ch[50];
  printf("Connection Established\n");
  recv(newsocket,buffer,sizeof(buffer),0);
  
  pid_t p1= fork();
  
  if(p1 == 0){
  FILE *fop = fopen(buffer,"r");
  
  if(fop == NULL){
  	strncpy(yo,"file not found\n",sizeof(yo));
  }  
  else
  {
  strncpy(yo,"",sizeof(yo));
  
  while(!feof(fop)){

 	strncpy(ch,"",sizeof(ch));
  	fgets(ch,sizeof(ch),fop);  	
  	strcat(yo,ch);

  }
  }
  printf("required file sent\n");
  send(newsocket,yo,sizeof(yo),0);
  }}while(1);
  
  close(newsocket);
  close(sockfd);
}

/*
OUTPUT:

s6cs107@comp49:~$ gcc -o ftps ftps.c
./s6cs107@comp49:~$ ./ftps
Server side
Connection Established
required file sent
Connection Established
required file sent

*/

//filename: (client)exp11

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


 sockfd=socket(AF_INET,SOCK_STREAM,0);
 struct sockaddr_in addr;


 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=5060;

 connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));

  printf("enter the filename: ");
  scanf("%s",buffer);
  send(sockfd,buffer,sizeof(buffer),0);
  
  char s[500];
  
  recv(sockfd,s,sizeof(s),0);
 	
  printf("%s",s);	

  close(sockfd);
}

/*
OUTPUT:

s6cs107@comp49:~$ gcc -o ftpc ftpc.c
s6cs107@comp49:~$ ./ftpc
Client side
enter the filename: lookup.txt
www.google.com	8.8.4.4
www.bing.com	4.4.4.4
stop
s6cs107@comp49:~$ ./ftpc
Client side
enter the filename: s'd;fl
file not found
s6cs107@comp49:~$ 

*/
