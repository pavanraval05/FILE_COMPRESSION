#include<ctype.h>

#define MAX_BUF 8

typedef struct tree {
    char ch; 
    struct tree *left;
    struct tree *right;
} tree;

void decompress_by_huffman(char *file_name);

void decode_file_huffman(tree A, int fd, char *file_name, int num_chars);

void destroy_tree(tree A);

void del_tree(tree *ptr);

