#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define RECUR (0)
#define DECOMP (0)
#define COMP (1)
#define HUFFMAN ((COMP) << 1)
#define LZW ((HUFFMAN) << 1)
#define DCT ((LZW) << 1)

#define COMP_HUFFMAN ((HUFFMAN) | (COMP)) 
#define COMP_LZW ((LZW) | (COMP))
#define COMP_DCT ((DCT) | (COMP)) 

#define DECOMP_HUFFMAN ((HUFFMAN) | (DECOMP)) 
#define DECOMP_LZW ((LZW) | DECOMP) 
#define DECOMP_DCT ((DCT) | DECOMP)

enum ERR_STATES {
    ERR_USAGE = -1, 
    ERR_COMP,     
    ERR_DECOMP,
    ERR_EXIT
};

void caller_function(int , char *);
void error_handler(int );

