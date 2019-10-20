#include"../FILE_IO/File_IO.h"
#include"huffman_compression.h"

/* The function calls different modules required
 * for creating a huffman tree for a given file.
 */

void compress_by_huffman(char *file_name) {
    int dist_chars;
    tree_elements *char_table;
    priority_quee *A;

    get_char_table(&char_table);
    get_char_freq(&char_table, file_name);
    dist_chars = get_dist_chars(char_table);
    create_priority_quee(&A, dist_chars, char_table);

    
    remove_priority_quee(A);
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
    close(fd);
}

int get_dist_chars(tree_elements *char_table) {
    int i = 0, count = 0;
    for(i = 0; i < NUM_CHARS; i++) {
        if(get_frequency(char_table, i) != 0) {
            count++;
        }
    }
    return count;
}

void create_priority_quee(priority_quee **A, int num_dist_char, tree_elements *char_table) {
    heap h;
    priority_quee temp, *ptr1, *ptr2;
    InitHeap(&h, num_dist_char);

    for(int i = 0; i < NUM_CHARS; i++) {
        if(get_frequency(char_table, i) != 0) {
            temp = get_heap_element(get_character(char_table, i), get_frequency(char_table, i));     
            Insert_minHeap(&h, temp);
        } 
    }
    printHeap(h);
    
    while(!isSizeOne(h)) {
        ptr1 = Remove_minHeap(&h);
        ptr2 = Remove_minHeap(&h); 
        temp = Create_subtree(ptr1, ptr2);
        Insert_minHeap(&h, temp);
    } 
    ptr1 = Remove_minHeap(&h);  
    *A = ptr1;

    destroyHeap(&h); 
    free(char_table); 
}



