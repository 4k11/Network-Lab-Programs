//filename: a.c(exp3)

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void main(){
	mkfifo("fifo1", 0666);
	
	int fd = open("fifo1", O_WRONLY);
	char buffer[100];
	
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		
		write(fd, buffer, strlen(buffer) + 1);
	}
}

//filename: b.c(exp3)

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void main(){
	mkfifo("fifo1", 0666);
	mkfifo("fifo2", 0666);
	
	int fd = open("fifo1", O_RDONLY);
	int fd2 = open("fifo2", O_WRONLY);
	char buffer[100];
	
	while (1) {
		read(fd, buffer, sizeof(buffer));
		
		int w = 1, s = 0, c = -1;
		
		for (int i = 0; buffer[i] != '\0'; ++i) {
			if (buffer[i] == ' ') {
				w++;
			}
			
			else if (buffer[i] == '.') {
				s++;
			}
			
			c++;
		}
		
		char str[100];
		
		sprintf(str, "chars: %d \nwords: %d \nsentences: %d\n", c, w, s);
		
		write(fd2, str, strlen(str) + 1);
	}
}

//filename: c.c(exp3)

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


void main(){
	int fd2 = open("fifo2", O_RDONLY);
	
	char buffer[100];
	while (1) {
		read(fd2, buffer, sizeof(buffer));
		
		printf("%s", buffer);
	}
}

/*

OUTPUT:

a.exe:

hello
hello world
hello world. Nice to meet you.

c.exe:

chars: 5 
words: 1 
sentences: 0
chars: 11 
words: 2 
sentences: 0
chars: 30 
words: 6 
sentences: 2




*/
