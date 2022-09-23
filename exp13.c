//filename: exp13.c[sliding window protocols]

//a. Stop and wait

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

int n,r,i=1;
scanf("%d",&n);

while(n!=0){

printf("sending frame %d",i);
srand(n);
r = rand()%2;

if(r==0){
printf("sending %d",i);
sleep(1);
printf("retransmitting %d",i);
}
printf("ack recvd for %d\n",i);
n -= 1;
i += 1;

}
}

//b. Go-back-N

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

int n,w,i=1,rec = 0, r;

printf("enter the number of packets: \n");
scanf("%d",&n);

printf("enter the window size: \n");
scanf("%d",&w);

srand(time(0));

while(i<=n){

rec = 0;

for(int j=i;j<i+w && j<=n;j++){
printf("\nsending packets: \n");
printf("%d",j);

}

for(int j=i;j<i+w && j<=n;j++){

r = rand()%2;
if(r!=0){

printf("\npacket %d ackgnd\n",j);
rec+=1;
}

else{

printf("\npacket %d not ackgnd\n",j);
printf("\nretransmitting\n");
break;
}
}

i+=rec;
}
}

//c. Selective repeat

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

int n,w,i=1,rec = 0, r , flag;

int t[100] = {0};

printf("enter the number of packets: \n");
scanf("%d",&n);

printf("enter the window size: \n");
scanf("%d",&w);

srand(time(0));

while(i<=n){

rec = 0;
flag = 0;

for(int j=i;j<i+w && j<=n;j++){
printf("\nsending packets: \n");
if(t[j]==0)
printf("%d",j);

}

for(int j=i;j<i+w && j<=n;j++){

if(t[j]==1){

if(flag!=1)
rec++;

continue;

}

r = rand()%2;
if(r!=0){

printf("\npacket %d ackgnd\n",j);
t[j]=1;
if(flag!=1)
rec+=1;
}

else{

printf("\npacket %d not ackgnd\n",j);
printf("\nretransmitting\n");
flag = 1;
break;
}
}

i+=rec;
}
}
