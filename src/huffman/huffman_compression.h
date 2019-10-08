#define NUM_CHARS 256

typedef struct huffman_tree_element {
    char ch;
    long int frequency;
} tree_elements;  

void compress_by_huffman(char *fil_name);

void get_char_table(tree_elements **char_table);

void Qsort_tree(tree_elements *arr, int left, int right);

void swap_tree_el(tree_elements *a, tree_elements *b);

void get_char_freq(tree_elements **char_table, char *file_name);

long int get_dist_chars(tree_elements *char_table);

void get_tree_elements(tree_elements **tree_list,int num_dist_char, tree_elements *char_table);
