#include <stdio.h>
#include <stdlib.h>

struct buffer{
    int *ptr;
    int size;
    int nu_elements;

    buffer(int initial_size){
        size = initial_size;
        ptr = (int *)malloc(sizeof(int) * size);
        if (!ptr)
            size = 0;
        nu_elements = 0;
    }

    ~buffer()
    {
        free(ptr);
        size = 0;
        nu_elements = 0;
    }

    void add(int element){
        if (nu_elements < size){
            ptr[nu_elements++] = element;
            return;
        }
        int new_size = size + 1;
        int *ptr_new = (int *)malloc(sizeof(int) * new_size);
        for(int i = 0; i < size; i++){
            ptr_new[i] = ptr[i];
        }
        ptr_new[nu_elements++] = element;
        size += 1;
        free(ptr);
        ptr = ptr_new;
    }

    void print_buffer(){
        int i;
        for(i = 0; i < nu_elements; i++){
            printf("%d ", ptr[i]);
        }
        printf("\n");
    }
};
typedef struct buffer buffer;

int main(){
    buffer b(3);

    for(int i = 1; i<5; i++){
        b.add(i);
        b.print_buffer();
    }

    return 0;
}
