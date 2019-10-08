#include"../FILE_IO/File_IO.h"
#include"huffman_compression.h"

/* The function calls different modules required
 * for creating a huffman tree for a given file.
 */

void compress_by_huffman(char *file_name) {
    long int dist_chars;
    tree_elements *tree_list, *char_table;
    
    get_char_table(&char_table);
    get_char_freq(&char_table, file_name);
    dist_chars = get_dist_chars(char_table);
    get_tree_elements(&tree_list ,dist_chars, char_table);  


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
        temp[i].ch = (char)i;
        temp[i].frequency = 0;
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
        temp[index].frequency += 1; 
    }  
}

long int get_dist_chars(tree_elements *char_table) {
    int i = 0, count = 0;
    for(i = 0; i < NUM_CHARS; i++) {
        if(char_table[i].frequency != 0) {
            count++;
        }
    }
    return count;
}

void get_tree_elements(tree_elements **tree_list, int num_dist_char, tree_elements *char_table) {
    tree_elements *temp; 
    int i = 0,index = 0; 
    temp = (tree_elements *)malloc(sizeof(tree_elements) * num_dist_char); 
    if(temp == NULL) {
        perror("The error is :");
        exit(errno);
    } 
    for(i = 0; i < NUM_CHARS; i++) {
        if(char_table[i].frequency != 0) {
            temp[index] = char_table[i];
            index++;
        }
    } 
    Qsort_tree(temp, 0, num_dist_char - 1);
    *tree_list = temp;
} 

void Qsort_tree(tree_elements *arr, int first, int last) {
    int i, j, pivot; 
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while(i < j) {
            while(arr[i].frequency <= arr[pivot].frequency && i < last) {
                i++;
            }
            while(arr[j].frequency > arr[pivot].frequency) {
                j--;
            }
            if(i < j) {
                swap_tree_el(arr + i, arr + j);
            }
        }
        swap_tree_el(arr + pivot, arr + j);
        Qsort_tree(arr, first, j - 1);
        Qsort_tree(arr, j + 1, last);
    }
}

/* Swap function for swaping tree_list data type.
 */
void swap_tree_el(tree_elements *a, tree_elements *b) {
    tree_elements temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
