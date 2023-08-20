/*
RDME is program that prints formatted Markdown.
Copyright (C) 2023  Luka Jovanović

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Contact: youshitsune@dmz.rs
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("usage: rdme FILE\n");
    } else if (argc > 2) {
        printf("usage: rdme FILE\n");
    } else {
        if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0){
            printf("usage: rdme FILE\n");
        }
        else{
            char *ctx = getctx(argv[1]);
            int file_size = getfilesize(argv[1]);

            int heading = FALSE;
            int code_block = FALSE;
            int bold = FALSE;
            int denote = FALSE;
            int first_tick = FALSE;
            int italic = FALSE;
            int ncode = 0;
            int nbold = 0;
            for (int i = 0; i < file_size; i++){
                if (heading == TRUE || code_block == TRUE || bold == TRUE || denote == TRUE || italic == TRUE){
                    if (heading == TRUE){
                        if (ctx[i] == '\n'){
                            printf("%c", ctx[i]);
                            heading = FALSE;
                        } else { 
                            printf("\033[1;38;2;%i;%i;%im%c\033[0m",header[0], header[1], header[2], ctx[i]);
                        }
                    } else if (bold == TRUE) {
                        if (ctx[i] == '*'){
                            if (nbold < 3) {
                                nbold++;
                            } else if (nbold == 3) {
                                bold = FALSE;
                                nbold = 0;
                            } 
                        } else {
                            if (nbold == 1){
                                italic = TRUE;
                                bold = FALSE;
                                printf("\033[3m%c\033[0m", ctx[i]);
                            } else {
                                printf("\033[1m%c\033[0m", ctx[i]);
                            }
                        }

                    } else if (code_block == TRUE){
                        if (ctx[i] == '`') { 
                            if (first_tick == TRUE){
                                printf("\033[1;38;2;%i;%i;%im%c\033[0m",block[0], block[1], block[2], ctx[i]);
                                first_tick = FALSE;
                            }
                            if (ncode < 5) {
                                ncode++;
                                printf("\033[1;38;2;%i;%i;%im%c\033[0m",block[0], block[1], block[2], ctx[i]);
                            } else if (ncode == 5) {
                                printf("\033[1;38;2;%i;%i;%im%c\033[0m",block[0], block[1], block[2], ctx[i]);
                                code_block = FALSE;
                                ncode = 0;
                            }
                        } else {
                            if (ncode == 1){
                                denote = TRUE;
                                code_block = FALSE;
                                printf("\033[1;38;2;%i;%i;%im`\033[0m", highlight[0], highlight[1], highlight[2]);
                                printf("\033[1;38;2;%i;%i;%im%c\033[0m", highlight[0], highlight[1], highlight[2], ctx[i]);
                            } else {
                            printf("\033[1;38;2;%i;%i;%im%c\033[0m",block[0], block[1], block[2], ctx[i]);
                            }
                        }
                    } else if (denote == TRUE) {
                        if (ctx[i] == '`') {
                            if (ncode == 1) {
                                denote = FALSE;
                                ncode = 0;
                                printf("\033[1;38;2;%i;%i;%im%c\033[0m", highlight[0], highlight[1], highlight[2], ctx[i]);
                            }
                        } else {
                                printf("\033[1;38;2;%i;%i;%im%c\033[0m", highlight[0], highlight[1], highlight[2], ctx[i]);
                        }
                    } else if (italic == TRUE) {
                        if (ctx[i] == '*') {
                            italic = FALSE;
                            nbold = 0;
                        } else {
                            printf("\033[3m%c\033[0m", ctx[i]);
                        }
                    }
                } else {
                    if (ctx[i] == '#' && (ctx[i-1]=='\n' || i == 0)) {
                        heading = TRUE;
                        printf("\033[1;38;2;%i;%i;%im%c\033[0m",header[0], header[1], header[2], ctx[i]);
                    } else if (ctx[i] == '`') {
                        code_block = TRUE;
                        ncode++;
                        first_tick = TRUE;
                    } else if (ctx[i] == '*') {
                        bold = TRUE;
                        nbold++;
                    } 
                    else {
                        printf("%c", ctx[i]);
                    }
                }
            }
        }
    }
}

