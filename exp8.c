//filename: exp8.c

#include <stdio.h>

struct node{

	unsigned dist[10];
	unsigned from[10];

}rt[10];

void main(){

	int n;
	int dmat[20][20];
	int count = 0;
	
	printf("enter the number of nodes: \n");
	
	scanf("%d",&n);
	
	printf("enter the cost matrix: \n");
	
	for(int i=0;i<n;i++){
	
	for(int j=0;j<n;j++){
	
		scanf("%d",&dmat[i][j]);
		dmat[i][i] = 0;
		rt[i].dist[j] = dmat[i][j];
		rt[i].from[j] = j;
	
	}
	}
	
	do{
		count = 0;
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		for(int k=0;k<n;k++){
		
			if(rt[i].dist[j]>rt[i].dist[k]+rt[k].dist[j]){
			rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
			rt[i].from[j]=k;
			count++;
			}
		}
		
	
	
	}while(count!=0);
	
	for(int i=0;i<n;i++){
	
		printf("\nstate value for router %d:\n",i+1);
	
		for(int j=0;j<n;j++){

		printf("\n\tnode %d via %d distance %d\n",j+1,rt[i].from[j]+1,rt[i].dist[j]);
		
		}
	
	printf("\n\n");
	}


}
/*
OUTPUT:

enter the number of nodes: 
4
enter the cost matrix: 
0
3
5
99
3
0
99
1
5
4
0
2
99
1
2
0

state value for router 1:

	node 1 via 1 distance 0

	node 2 via 2 distance 3

	node 3 via 3 distance 5

	node 4 via 2 distance 4



state value for router 2:

	node 1 via 1 distance 3

	node 2 via 2 distance 0

	node 3 via 4 distance 3

	node 4 via 4 distance 1



state value for router 3:

	node 1 via 1 distance 5

	node 2 via 4 distance 3

	node 3 via 3 distance 0

	node 4 via 4 distance 2



state value for router 4:

	node 1 via 2 distance 4

	node 2 via 2 distance 1

	node 3 via 3 distance 2

	node 4 via 4 distance 0

*/
