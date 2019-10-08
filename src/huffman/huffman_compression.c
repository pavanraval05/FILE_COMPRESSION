#include"../FILE_IO/File_IO.h"
#include"huffman_compression.h"

/* The function calls different modules required
 * for creating a huffman tree for a given file 
 */

void compress_by_huffman(char *file_name) {
    char *arr;
    long int num_tree_el;
    tree_elements *tree_el;

    sort_file(file_name, arr);
    num_tree_el = get_dist_chars(arr);
    tree_el = get_tree_elements(arr, num_tree_el);
    Qsort_tree(tree_el,0, num_tree_el - 1);
    free(arr);
    free(tree_el);
}

void sort_file(char file_name, char *arr) {    
    int fd;
    long int file_size = 0;
    open_file_read(&fd, file_name);
    if((file_size = get_file_size(file_name)) != -1) {
        arr = get_file_chars(fd, file_size + 1); 
        Qsort_file(arr, 0, file_size - 1);
        arr[file_size] = '\0';
    } 
    else {
        printf("Error can't access the file status\n");
        exit(1);
    }
return arr;
}

void Qsort_file(char *arr, long int first, long int last){
    long int i, j, pivot;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;

        while(i < j) {
            while(arr[i] <= arr[pivot] && i < last)
                i++;
            while(arr[j] > arr[pivot])
                j--;
            if(i < j) {
                swap_chars(arr + i, arr + j);
            }
        }
        swap_chars(arr + pivot, arr + j);
        Qsort_file(arr, first, j - 1);
        Qsort_file(arr, j + 1, last);
    }
}

void swap_chars(char *a, char *b) { 
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Qsort_tree(tree_elements *arr, int first, int last) {
    int i, j, pivot; 
    if(first < last) {
        pivot = first;
        i = first;
        j = last;

        while(i < j) {
            while(arr[i].frequency <= arr[pivot].frequency && i < last)
                i++;
            while(arr[j].frequency > arr[pivot].frequency)
                j--;
            if(i < j) {
                swap_tree_el(arr + i, arr + j);
            }
        }
        swap_tree_el(arr + pivot, arr + j);
        Qsort_tree(arr, first, j - 1);
        Qsort_tree(arr, j + 1, last);
    }
}

void swap_tree_el(tree_elements *a, tree_elements *b) {
    tree_elements temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

long int get_dist_chars(char *arr) {
    long int count = 0,i = 0;
    for(i = 1; arr[i] != '\0'; i++) {
        if(arr[i-1] == arr[i]) {
            continue;
        }
        else {
            count++;
        }
    }
return count + 1; 
}

tree_elements *get_tree_elements(char *arr, long int num_dist_chars) {
    tree_elements *temp = NULL;
    long int i =0;
    temp = (tree_elements *)malloc(sizeof(tree_elements) * num_dist_chars);
    for(i = 0; i < num_dist_chars; i++) {
        temp[i] = get_next_token(arr);
    }
    return temp;
} 

tree_elements get_next_token(char *arr) {
    static int index = 0;
    int freq = 0, j = index;
    tree_elements token;
    
    if(arr[index] == '\0') {
        token.ch = '\0';
        token.frequency = -1;
        return token;
    }
    for(; arr[j] == arr[index]; index++) {
        freq++; 
    }
    token.ch = arr[j];
    token.frequency = freq; 
return token;
}

