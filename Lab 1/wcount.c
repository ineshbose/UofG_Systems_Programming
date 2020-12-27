#include <stdio.h>
#include <ctype.h>

int main(){
	long long nw = 0LL;
	int c;
    int state = 0;

	while((c = getchar()) != EOF){
		if(!isalpha(c)){
			state = 0;
        }
		else if(state == 0){
			state = 1;
			nw++;
		}
    }
	printf("%lld\n", nw);
	return 0;
}
