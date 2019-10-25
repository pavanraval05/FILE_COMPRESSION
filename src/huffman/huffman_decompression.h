#include<ctype.h>

#define RESULTS "results/"
#define MAX_BUF 8
#define MAX 128

typedef struct tree {
    char ch; 
    struct tree *left;
    struct tree *right;
} tree;

void check_file_extention(char *str);

void decompress_by_huffman(char *file_name);

void decode_file(tree A, int fd, char *file_name, int num_chars);

void tokenize_file_name(char *ans, char *file_name);

void destroy_tree(tree A);

void del_tree(tree *ptr);

