#include"caller.h"
#include"../huffman/huffman_compression.h"


void caller_function(int call_algo, char *file_name) {
    switch(call_algo) {
        case COMP_HUFFMAN :
            compress_by_huffman(file_name);
            break;
        case COMP_LZW :
            printf("Here compression by LZW will be done\n");
            break;
        case COMP_DCT :
            printf("Here compression by DCT will be done\n");
            break;
        case DECOMP_HUFFMAN :
            printf("Here decompression by huffman will be done\n");
            break;
        case DECOMP_LZW :
            printf("Here decompression by LZW will be done\n");
            break;
        case DECOMP_DCT :
            printf("Here decompression by DCT will be done\n");
            break;
        default :
            error_handler(call_algo);
            break;
    }
}

void error_handler(int err_num) {
    switch(err_num) {
        case ERR_USAGE :
            printf("Usage: ./kishan [COMP_FLAGS / DECOMP_FLAGS]... filename...\n");
            printf("Try ./kishan --help for more information.\n");
            exit(1);
        case ERR_COMP :     
            printf("Unkown / Missing arguments for decompression\n");
            exit(1);
        case ERR_DECOMP :
            printf("Unkown / Missing arguments for compression\n");
            exit(1);
        case ERR_EXIT :
            exit(1);
    }
}



