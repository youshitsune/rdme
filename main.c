#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"

#define TRUE 1
#define FALSE 0

int 
getfilesize(char file_name[]){
    if (access(file_name, F_OK) != 0){
        printf("rdme: %s: No such file\n", file_name);
        return -1;
    }
    FILE *fp;
    fp = fopen(file_name, "r");
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fclose(fp);
    return file_size;
}

char 
*getctx(char file_name[]){
    FILE *fp;
    fp = fopen(file_name, "r");

    char *ctx = malloc(getfilesize(file_name));
    char c = getc(fp);
    int i = 1;
    ctx[0] = c;
    while (c != EOF){
        c = getc(fp);
        ctx[i] = c;
        i++;
    }

    return ctx;
}

int 
main(int argc, char *argv[]){
    if (argc < 2) {
        printf("usage: rdme FILE");
    } else if (argc > 2) {
        printf("usage: rdme FILE");
    } else {

        char *ctx = getctx(argv[1]);
        int file_size = getfilesize(argv[1]);

        int heading = FALSE;
        for (int i = 0; i < file_size; i++){
            if (heading == TRUE){
                if (ctx[i] == '\n'){
                    printf("%c", ctx[i]);
                    heading = FALSE;
                } else { 
                    printf("\033[1;38;2;%i;%i;%im%c\033[0m",rgb[0], rgb[1], rgb[2], ctx[i]);
                }
            } 
            else if (heading == FALSE){
                if (ctx[i] == '#'){
                    heading = TRUE;
                    printf("\033[1;38;2;%i;%i;%im%c\033[0m",rgb[0], rgb[1], rgb[2], ctx[i]);
                } else {
                    printf("%c", ctx[i]);
                }
            }
            
        }
    }
}

