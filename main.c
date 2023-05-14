#include <stdio.h>

#ifdef WIN32
    #include <io.h>
    #define F_OK 0
    #define access _access
#else
    #include <unistd.h>
#endif
    

#define TRUE 1
#define FALSE 0 

int 
main(int argc, char *argv[]){
    if (argc < 2) {
        printf("HELP:");
    } else if (argc > 2) {
        printf("HELP:");
    } else {
        FILE *fp;
        if (access(argv[1], F_OK) != 0){
            printf("rdme: %s: No such file\n", argv[1]);
            return -1;
        }
        fp = fopen(argv[1], "r");
        fseek(fp, 0, SEEK_END);
        int file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char ctx[file_size];
        int c = getc(fp);
        int i = 1;
        ctx[0] = c;
        while (c != EOF){
            c = getc(fp);
            ctx[i] = c;
            ++i;
        }

        int heading = FALSE;
        for (int i = 0; i < file_size; i++){
            if (heading == TRUE){
                if (ctx[i] == '\n'){
                    printf("%c", ctx[i]);
                    heading = FALSE;
                } else { 
                    printf("\033[1;31m%c\033[0m", ctx[i]);
                }
            } 
            else if (heading == FALSE){
                if (ctx[i] == '#'){
                    heading = TRUE;
                    printf("\033[1;31m%c\033[0m", ctx[i]);
                } else {
                    printf("%c", ctx[i]);
                }
            }
            
            }
        }
        
        
}

