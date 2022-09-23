//filename: exp12.c

#include <stdio.h>

int main(){

	int bsize, outrate, n , isize, remain, discard, out;
	
	printf("enter the bucket size: \n");
	scanf("%d",&bsize);
	
	remain = bsize;
	
	printf("enter the output rate: \n");
	scanf("%d",&outrate);
	
	printf("enter the number of inputs: \n");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
	
	
		discard = 0;
		
		printf("enter the input size: \n");
		scanf("%d",&isize);
		
		if(isize>remain){
		
		discard = isize -remain;
		remain = 0;
		
		}
		else{
		
		remain -= isize; 
		
		}
		
		if(outrate>bsize-remain)
		
		out = bsize -remain;
		
		else
		
		out = outrate;
		
		remain += out;
		printf("total stored in bucket: %d\n",bsize-remain);
		printf("outputted: %d\n",out);
		printf("discarded: %d\n",discard);
	}
}
