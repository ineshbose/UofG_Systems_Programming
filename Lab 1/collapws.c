#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    int c;
    int state = 0;

    while((c = getchar()) != EOF){
        switch(state){
            case 2: putchar(c);
                    if(c == '"'){
                        state = 0;
                    }
                    break;
            case 1: if(isspace(c)){
                        state = 0;
                        putchar(' ');
                    }
                    else if(c == '"'){
                        putchar(c);
                        state = 2;
                    }
                    else{
                        putchar(c);
                    }
                    break;
            case 0: if(!isspace(c)){
                        putchar(c);
                        state = (c == '"') ? 2 : 1;
                    }
                    break;
            default: exit(1);
        }
    }
    putchar('\n');
    return 0;
}
