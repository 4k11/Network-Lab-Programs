//filename: (server)exp9[DNS SERVER]

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
   char str[50],url[50],ip[50];
   int sfd, flag;
   struct sockaddr_in addr;
   
   FILE *fin;
   
   
   addr.sin_family=AF_INET;
   addr.sin_addr.s_addr=INADDR_ANY;
   addr.sin_port=3008;
   int s=sizeof(struct sockaddr_in);
   
   sfd = socket(AF_INET,SOCK_DGRAM, 0);
   bind(sfd,(struct sockaddr *)&addr, sizeof(addr));
   
   do
   {
      fin = fopen("dns.txt","r");
      recvfrom(sfd,str,sizeof(str),0,(struct sockaddr *)&addr,&s);
      printf("\nRequest: %s\n",str);
      flag = 0;
      
      
      while(!feof(fin))
      {
        fscanf(fin,"%s\t%s",url,ip);
        if(strcmp(url, str)==0)
        {
           
           strcpy(str,"IP: ");
           strcat(str, ip);
           flag =1;
           break;
         }
         else
             if(strcmp(ip,str)==0)
             {
               strcpy(str, "URL: ");
               strcat(str,url);
               flag=1;
               break;
               }
           }
           if(flag==0)
             strcpy(str, "Domain not found!");
            sendto(sfd,str,sizeof(str),0,(struct sockaddr *)&addr,s);
           }while(1);
           
           close(sfd);
           fclose(fin);
         }
         
//filename: (client)exp9[DNS SERVER]

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
 char str[50];
 int sockfd;


 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 struct sockaddr_in addr;


 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=3008;
 
 int s=sizeof(struct sockaddr_in);
 connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));

  printf("Enter request: ");
  scanf("%s",str);
  
  sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&addr,s);
  recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&addr,&s);
  
  printf("%s\n",str);
  
  close(sockfd);
}


/*filename: (dns.txt)exp9[DNS SERVER]

www.google.com 8.8.4.4
www.facebook.com 8.8.8.8

*/

//OUTPUT

/*

server:
s6cs107@comp49:~$ gcc -o dnss dnss.c
s6cs107@comp49:~$ ./dnss

Request: www.google

Request: www.google.com


client:

s6cs107@comp49:~$ gcc -o dnsc dnsc.c
s6cs107@comp49:~$ ./dnsc
Enter request: www.google
Domain not found!
s6cs107@comp49:~$ ./dnsc
Enter request: www.google.com
IP: 8.8.4.4


*/
         
  
