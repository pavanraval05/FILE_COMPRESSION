#include"../FILE_IO/File_IO.h"
#include"huffman_compression.h"

/* The function calls different modules required
 * for creating a huffman tree for a given file.
 */

void compress_by_huffman(char *file_name) {
    long int dist_chars;
    tree_elements *char_table;
    priority_quee A;

    get_char_table(&char_table);
    get_char_freq(&char_table, file_name);
    dist_chars = get_dist_chars(char_table);
    create_priority_quee(&A, dist_char, char_table);

}

/* The Function constructs a character table.
 * The tables has 256 distinct characters as per
 * ASCII table and initializes the frequency of 
 * each character to zero.
 */

void get_char_table(tree_elements **char_table) {
    int i = 0;
    tree_elements *temp;
    temp = (tree_elements *)malloc(sizeof(tree_elements) * NUM_CHARS);
    if(temp == NULL) {
        perror("The error is :");
        exit(1);
    }
    for(i = 0; i < NUM_CHARS; i++) {
        write_charachter(temp + i, (char)i);
        write_frequency(temp + i, 0);
    }
    *char_table = temp;
}

/* Function gets the frequency of characters appearing
 * in the file , stores it in the char_table.  
 */

void get_char_freq(tree_elements **char_table, char *file_name) {
    int fd = 0, index = 0;
    char c;
    tree_elements *temp = *char_table;
    open_file_read(&fd, file_name);
    while(freadchar(fd, &c)) {
        index = (int)c; 
        write_frequency(temp + index, get_frequency(temp, index) + 1);
    }  
}

long int get_dist_chars(tree_elements *char_table) {
    int i = 0, count = 0;
    for(i = 0; i < NUM_CHARS; i++) {
        if(get_frequency(char_table, i) != 0) {
            count++;
        }
    }
    return count;
}

