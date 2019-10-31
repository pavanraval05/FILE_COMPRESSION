#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "caller/caller.h"

int main(int argc, char* argv[]) {
    int c = 0, caller_flag = 0;
    char *file_name = NULL; 

    if(argc == 1) {
        caller_flag = -1; 
    }
    while((c = getopt(argc, argv, "cdh:l:i:R")) != -1) {
        switch(c) {
            case 'c':
                caller_flag |= COMP;
                break;
            case 'd':
                caller_flag |= DECOMP;
                break;
            case 'h':
                caller_flag |= HUFFMAN;
                file_name = optarg;
                break;
            case 'l':
                caller_flag |= LZW;
                file_name = optarg;
                break;
            case 'i':
                caller_flag |= DCT;
                break;
            case 'R':
                caller_flag |= RECUR;
                break;
            default:
                error_handler(ERR_EXIT);
                break;
        }
    }    
    caller_function(caller_flag, file_name);
    return 0;
}

