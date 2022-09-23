#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){

	int pfd1[2], pfd2[2];
	
	if(pipe(pfd1)<0){
		return 0;
	}
	
	if(pipe(pfd2)<0){
		return 0;
	}
	
	if(fork() > 0){
		
		close(pfd1[0]);
		close(pfd2[1]);
		char file_name[] = "yo.txt";
		write(pfd1[1], file_name, strlen(file_name));
		wait();
		char file_content[100];
		read(pfd2[0], file_content, 100);
		printf("%s", file_content);
		
	}
	
	else{
		close(pfd1[1]);
		close(pfd2[0]);
		char file_name[100];
		read(pfd1[0], file_name, 100);
		FILE * file = fopen(file_name, "r");
		char file_content[100];
		fgets(file_content , 100 ,file);
		write(pfd2[1], file_content, 100);
	}
	return 0;
}

/*yo.txt

hello world

output:

hello world

*/

