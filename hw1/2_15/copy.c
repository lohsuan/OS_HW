#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

bool file_exists(char *file_name) {
    FILE *file_ptr = fopen(file_name, "r");
    if (!file_ptr) {
        return false;
    }
    return true;
}

void copy(char *out_str, char *in_str) {
    
    int c; // store one char at a time

    FILE *in_ptr = fopen(in_str, "r");
    FILE *out_ptr = fopen(out_str, "w");

    if (!in_ptr) {
        perror("Source file can't be opened: ");
        exit(1);
    }
    if (!out_ptr) {
        perror("Destination file can't be opened: ");
        exit(1);
    }

    // copy file one char at a time 
    while ((c = fgetc(in_ptr)) != EOF) {
        fputc(c, out_ptr);
    }

    printf("\nSuccessfully copy %s's content to %s !\n", in_str, out_str);
    fclose(in_ptr);
    fclose(out_ptr);
}

int main() {
    char str[32], in_str[32], out_str[32];
    char *str_ptr = str;
    char *in_ptr = in_str;
    char *out_ptr = out_str;

    // get name of source file from keyboard
    while (strcmp(in_str, "")) { // while in_str is empty
        printf("Please enter the name of source file: ");
        scanf("%s", str_ptr);
        
        if (file_exists(str_ptr)) {
            strcpy(in_str, str);
            break;
        }
        else {
            printf("File can't be opened!\n");
            continue;
        }
    }

    // get name of destination file from keyboard
    while (strcmp(out_str, "")) { // while out_str is empty
        printf("Please enter the name of destination file: ");
        scanf("%s", str_ptr);
        
        if (!file_exists(str_ptr)) {
            strcpy(out_str, str);
            break;
        }
        else {
            printf("File already exists!\n");
            continue;
        }
    }

    copy(out_str, in_str);

    return EXIT_SUCCESS; 
}