#include "caller.h"
#include "../huffman/huffman_compression.h"
#include "../huffman/huffman_decompression.h"
#include "../LZW/LZW_compression.h"
#include "../LZW/LZW_decompression.h"
#include "../DCT/DCT_compression.h"


void caller_function(int call_algo, char *file_name) {
    switch(call_algo) {
        case COMP_HUFFMAN :
            compress_by_huffman(file_name);
            break;
        case COMP_LZW :
            compress_by_LZW(file_name);
            break;
        case COMP_DCT :
            compress_by_DCT(file_name);
            break;
        case DECOMP_HUFFMAN :
            decompress_by_huffman(file_name);
            break;
        case DECOMP_LZW :
            decompress_by_LZW(file_name);
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



