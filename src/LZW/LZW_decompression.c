#include "LZW_decompression.h"
#include "../FILE_IO/File_IO.h"

/* The functions initializes a intial dictionary for
 * the decoder. Call the decode file function to 
 * decompress the file.
 */

void decompress_by_LZW(char *file_name) {
    DICT A;
    // Initializes the Dictionary with same size as of Encoder.
    initialize_dictionary(&A, DICT_SIZE);
    // Decodes the file 
    decode_file_LZW(file_name, &A); 
}

/* Decodes the compressed files using a dictionary
 * Note - dictionary implemented is dynamic (Grows as more
 * character sequences are decoded.)
 */

void decode_file_LZW(char *file_name, DICT *A) {
    int fd, fdd;
    int index, bit_string_read, cur_len = BIT_LEN, temp, len, index_dic, curr_index;
    char prev[32], curr[32], output_file[128], BUFFER = 0, str[32];
    
    // Check for valid - file-extension  
    check_file_extention(file_name);
    // For storing the result in a suitable folder 
    tokenize_file_name(output_file, file_name);

    open_file_read(&fd, file_name);
    open_file_write(&fdd, output_file);

    bit_string_read = 0;
    index = 0;
    temp = 0;
    prev[0] = '\0';
    curr[0] = '\0';
    str[0] = '\0';
    // Variables for keeping track of Dictionary size
    index_dic = NUM_CHARS;
    curr_index = DICT_SIZE;
    
    printf("Decompression %s by LZW algorithm\n", file_name);

    while(freadchar(fd, &BUFFER)) {
        // Store the Bits in BUFF space.
        for(;(index < READ_BUF) && (bit_string_read < cur_len); index++) {
            if(BUFFER & 128) {
                str[bit_string_read] = '1';
            }
            else {
                str[bit_string_read] = '0';
            }
            BUFFER = BUFFER << 1;
            bit_string_read++;
        }
        // If bit string is of cur_len then 
        // write the output in decompressed file.
        
        if(bit_string_read == cur_len) {
            str[bit_string_read] = '\0';
            // Get decimal value 
            temp = convert_string_to_decimal(str);

            // Special case where dictionary key which is yet to 
            // be formed is called for decoding.
            if(temp == index_dic) {
                len = strlen(prev);
                prev[len] = curr[0]; 
                prev[len + 1] = '\0';
                
                // Add the new sequence to dictionary.
                add_in_dictionary(A, prev, index_dic);
                
                // For Dynamically growing the size of dictionary
                if(index_dic  == curr_index - 1) {
                    update_dictionary(A, index_dic);
                    curr_index = curr_index << 1;
                    cur_len += 1;
                } 
               
                index_dic++;
                // Write decoded charcater as output.
                write(fdd, prev, strlen(prev));
                
            }
            else {
                strcpy(curr, (*A)[temp].key);
                // Write decoded charcater as output.
                write(fdd, curr, strlen(curr));

                if(strlen(prev) != 0) {
                    len = strlen(prev); 
                    prev[len] = curr[0];
                    prev[len + 1] = '\0';
                    
                    // Add the new sequence to dictionary concatenating
                    // previous with current.
                    add_in_dictionary(A, prev, index_dic);
                    index_dic++;
                    
                    // For Dynamically growing the size of dictionary
                    if(index_dic  == curr_index - 1) {
                        update_dictionary(A, index_dic);
                        curr_index = curr_index << 1;
                        cur_len += 1;
                    } 

                } 
                // Store the current sequence
                strcpy(prev, curr);
            } 
            bit_string_read = 0;
            // Traverse the buffer for remaining bits if left in BUFFER
            for(;index < READ_BUF; index++) {
                if(BUFFER & 128) {
                    str[bit_string_read] = '1';
                }
                else {
                    str[bit_string_read] = '0';
                }
                BUFFER = BUFFER << 1;
                bit_string_read++;
            }
            index = 0;
            BUFFER = 0;
        }  
        if(index == READ_BUF) {
            index = 0;
            BUFFER = 0;
        } 
    }
}

/* Given a string containing binary digits 1 and 0,
 * function returns the equivalent decimal value. 
 */

int convert_string_to_decimal(char *str) {
    int temp = 0, i, pow = 1;
    for(i = strlen(str) - 1; i >= 0; i--) {
        if(str[i] == '1') {
            temp += pow;
        }
        pow = pow * 2;
    }
    return temp;
}

