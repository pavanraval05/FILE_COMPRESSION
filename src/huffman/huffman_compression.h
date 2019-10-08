typedef struct huffman_tree_element {
    char ch;
    long int frequency;
} tree_elements;  

void compress_by_huffman(char *fil_name);

char *sort_file(char *file_name);

void Qsort_file(char *arr, long int left, long int right);

void swap_chars(char *a, char *b);

void Qsort_tree(tree_elements *arr, int left, int right);

void swap_tree_el(tree_elements *a, tree_elements *b);

tree_elements *get_tree_elements(char *arr, long int get_dist_chars);

long int get_dist_chars(char *arr);

tree_elements get_next_token(char *arr);


