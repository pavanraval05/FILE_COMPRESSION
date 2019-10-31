#include "huffman_decompression.h"
#include "canonical_map.h"
#include "../FILE_IO/File_IO.h"

/* Calls different Modules for required for decompression
 */

void decompress_by_huffman(char *file_name) {
    int fd, i, j ,len, file_size;
    unsigned int num_chars = 0;
    codebook *code_table, *canonical_codes;
    tree A, *ptr = NULL;
    
    // Check for file_extension and get file_size
    check_file_extention(file_name);                       
    file_size = get_file_size(file_name);  

    // OPEN compressed file and read the 2st byte
    // The first two bytes denotes number of symbol-bit_length pair 
    open_file_read(&fd, file_name);
    read(fd, &num_chars, 2);
    file_size = file_size - 2;

    code_table = get_codebook(num_chars);
    for(i = 0; i < num_chars; i++) {
        len = 0;
        read(fd, &len, 1);
        read(fd, &(code_table[i].symbol), 1);
        file_size = file_size - 2;
        for(j = 0; j < len; j++) {
            code_table[i].str[j] = '0'; 
        }
        code_table[i].str[len] = '\0';
    }    
    
    // Map the bit lengths to get canonical codes.
    canonical_codes = map_bit_strings(code_table, num_chars);
    
    // Form a tree based on the canonical codes.
    // A is the root node.
    A.left = A.right = NULL;
    for(i = 0; i < num_chars; i++) {
        ptr = &A;
        for(j = 0; j < strlen(canonical_codes[i].str); j++) {
            if(canonical_codes[i].str[j] == '0') {
                if(ptr->left == NULL) {
                    ptr->left = (tree *)malloc(sizeof(tree)); 
                    ptr->left->left = ptr->left->right = NULL; 
                    ptr->left->ch = EOF;
                }
                ptr = ptr->left;
            }
            else {
                if(ptr->right == NULL) {
                    ptr->right = (tree *)malloc(sizeof(tree)); 
                    ptr->right->left = ptr->right->right = NULL; 
                    ptr->right->ch = EOF;
                } 
                ptr = ptr->right;
            }
        } 
        ptr->ch = canonical_codes[i].symbol;
    }  

    // Laslty decode the file with the tree re-generated 
    decode_file_huffman(A, fd, file_name, file_size - 2); 

    destroy_tree(A);
    free(code_table);
    free(canonical_codes);
}

/* The function decodes the compressed file and writes the output 
 * in another file (in result folder). Arguments passed to function 
 * include tree, file_dispritor of compressed file, filename and last 
 * read_bytes. Read_bytes is passed as argument is solve the problem 
 * of how much to read when we encounter reading of last BIT-STRING
 */

void decode_file_huffman(tree A, int fd, char *file_name, int read_bytes) {
    tree *ptr;
    uint8_t BUFFER, FIRST_BIT = 0;    
    int index, fdd, last_bits = 0;
    char decomp_file[MAX];  
    
    // Tokenize the file_name to store result in appropiate folder
    tokenize_file_name(decomp_file, file_name); 
    open_file_write(&fdd, decomp_file);

    printf("Decoding %s using huffman algorithm ...\n", file_name);
    ptr = &A;
    FIRST_BIT = 1 << (MAX_BUF - 1); 
    
    // DECODES the BIT-STRINGS (except the last one) 
    while(read_bytes > 0) {
        read(fd, &BUFFER, 1);
        index = 0;
        while(index != MAX_BUF) {
            // For every BIT traverese the tree
            if(BUFFER & FIRST_BIT) {
                ptr = ptr->right;    
                index++;
            }
            else {
                ptr = ptr->left; 
                index++;
            }
            BUFFER = BUFFER << 1;
            // Checks if node is a leaf
            if(!ptr->left && !ptr->right) {
                write(fdd, &(ptr->ch), 1);
                ptr = &A;
            }
        }
        read_bytes = read_bytes - 1;
    }    
    
    read(fd, &BUFFER, 1);
    read(fd, &last_bits, 1);
    // Here last_bits tells number of bits to read for last BIT-STRING
    last_bits = MAX_BUF - last_bits;
    
    // Get the result of the last BIT-STRING
    while(last_bits > 0) {
        if(BUFFER & FIRST_BIT) {
            ptr = ptr->right;    
        }
        else {
            ptr = ptr->left; 
        }
        BUFFER = BUFFER << 1;
        if(!ptr->left && !ptr->right) {
            write(fdd, &(ptr->ch), 1);
            ptr = &A;
        }
        last_bits = last_bits - 1;
    }
    close(fdd);
    close(fd);
}

/* Removes the tree structure by freeing
 * all memory allocated by malloc
 */

void destroy_tree(tree A) {
    del_tree(A.left);
    del_tree(A.right);
}

void del_tree(tree *ptr) {
    if(ptr != NULL) {
        del_tree(ptr->left);
        del_tree(ptr->right);
        free(ptr);
    }
}
