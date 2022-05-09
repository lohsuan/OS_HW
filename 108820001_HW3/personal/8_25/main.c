#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    unsigned int address, pageNum, offset;
    unsigned int pageSize = pow(2, 12);

    if(argc != 2){
        printf("Please enter the virtual address.\n");
        return 1;
    }

    address = atoi(argv[1]);
    printf("The address %d contains: \n", address);

    pageNum = address / pageSize;
    offset = address % pageSize;

    printf("page number = %d\n", pageNum);
    printf("offset = %d\n", offset);

    return 0;
}