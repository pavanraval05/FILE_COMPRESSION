#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include"huffman_compression.h"

int i = 0,c_flag = 0, d_flag = 0, r_flag = 0;

void call_compression(char *str, char *filename);

void call_de_compression(char *str, char *filename);

int main(int argc, char* argv[]) {

    while(--argc) {
        if(*argv[++i] == '-') {
            switch(*(argv[i]+1)) {
                case 'c':
                    call_compression(argv[i]+1,argv[i+1]);
                    argc--;
                    i++;
                    break;
                case 'd':
                    call_de_compression(argv[i]+1,argv[i+1]);
                    argc--;
                    i++;
                    break;
                case 'R':
                    r_flag = 1;
                    printf("The -R flag is set to 1\n");
                    break;
                default:
                    printf("Usage of code: ./exe flag filename\n");
                    exit(1);
                    break;
            }
        }
        else {
            printf("Usage of code: ./exe flag filename\n");
            exit(1);    
        }
    } 
    return 0;
}

void call_compression(char *str,char *filename) {
    if(strlen(str) == 1 && !c_flag) {
        c_flag = 1;
        if(filename!=NULL) {
            compress_by_huffman(filename);
        } 
        else {
            printf("Undefined behaviour try using --help\n");
            exit(1);
        }
    }
    else {
        printf("Undefined behaviour try using --help\n");
        exit(1); 
    }
}

void call_de_compression(char *str, char *filename) {

}

