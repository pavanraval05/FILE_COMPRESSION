#define NUM_CHARS 256
#include"heap.h"

void compress_by_huffman(char *fil_name);

void get_char_table(tree_elements **char_table);

void get_char_freq(tree_elements **char_table, char *file_name);

long int get_dist_chars(tree_elements *char_table);

void create_priority_quee(priority_quee *A, int num_dist_char, tree_elements *char_table);






