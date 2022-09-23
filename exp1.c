#include <stdio.h>
#include <unistd.h>

int main(){

	printf("enter the no: of elements: \n");
	int n;
	scanf("%d",&n);
	
	printf("enter the numbers: \n");
	int a[n];
	for(int i=0;i<n;++i)
	scanf("%d",a+i);
	
	for(int i=0;i<n-1;++i){
		for(int j=0;j<n-1;++j){
			if(a[j] > a[j+1]){
				int t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
				
			}	
		}
	}

	if(fork() > 0){
	
		printf("parent process says: ");
		for(int i=0;i<n;++i)
		printf("%d ",a[i]);
		wait();
	}
	else{
		printf("child process says: ");
		for(int i=n-1;i>=0;i--)
		printf("%d ",a[i]);
	}
	return 0;
} 


/*
OUTPUT:

enter the no: of elements: 
3
enter the numbers: 
4
5
3
child process says: 5 4 3 parent process says: 3 4 5

*/
