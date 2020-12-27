#include <stdio.h>

int main(){
	int c;
	int lastc = '\n';
	long long nlines = 0LL;

	while((c = getchar()) != EOF){
		lastc = c;
		if(c == '\n'){
			nlines++;
        }
	}
	if(lastc != '\n'){
		nlines++;
    }
	printf("%lld\n", nlines);
	return 0;
}