#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

int readline(char line[], int max){
	if(fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

int writeline(const char line[]){
	fputs(line, stdout);
	return strlen(line);
}

int main(){
	char buf[MAXLINE];

	while(readline(buf, MAXLINE)){
		writeline(buf);
    }
	return 0;
}