#include "LZW_compression.h"
#include "../FILE_IO/File_IO.h"

/* Functions Initializes a dictionary (initial Codebook) for
 * encoder. Also calls function for encoding the file.
 */

void compress_by_LZW(char *file_name) {
    DICT A;  
    // Initializes the Dictionary with suitable size.
    initialize_dictionary(&A, DICT_SIZE);
    // Encodes the file 
    encode_file_LZW(&A, file_name);
}

/* Encodes the sequence on characters in file with the dictionary 
 * value for the character or character sequence. 
 * Note - The Dictionary implemented is Dynamic (Grows in size with file)
 */

void encode_file_LZW(DICT *A,char *file_name) {
    int fd, fdc, currstate, nextstate, index, i, curr_index, curr_bit_len;
    char ch, str[MAX_SEQUENCE], temp[MAX_SEQUENCE];

    printf("Encoding %s using LZW Algorithm ...\n", file_name);

    open_file_read(&fd, file_name); 
    strcat(file_name, EXT);
    // File for writing the compressed ouput
    open_file_write(&fdc, file_name);

    currstate = START;        
    index = ASCII_CHARS;  
    curr_bit_len = BIT_LEN;
    curr_index = DICT_SIZE; 

    /* States used for writing the encoded output corresponding to
     * Character sequence present in dictionary are :-
     * 1. START       - character read by start state will always be there 
     *                  in the dictionary.
     * 2. IN_DICT     - previous read character sequence was in dictionary. 
     * 3. NOT_IN_DICT - previous read character sequence was not in dictionary.
     * 4. STOP        - File character sequence has been encoded. 
     */

    while(currstate != STOP) {
        switch(currstate) {
            case START:
                if(freadchar(fd, &ch) != 0) {
                    str[0] = ch;
                    str[1] = '\0';
                    // Character read will definately be the dictionary
                    nextstate = IN_DICT;
                } 
                else {
                    nextstate = STOP;
                }
                break;
            case IN_DICT:
                if(freadchar(fd, &ch) != 0) {
                    temp[0] = ch;
                    temp[1] = '\0';
                    
                    // Concatenate the curr character with previous sequence
                    // Check for the new sequence in the dictionary.
                    strcat(str, temp);
                    if(search_in_dictionary(str) != -1) {
                        nextstate = IN_DICT;
                    } 
                    else {
                        nextstate = NOT_IN_DICT;
                    }
                }
                else {
                    nextstate = STOP;
                }
                break;
            case NOT_IN_DICT:
                // For Dynamically inscresing the size of Dictionary
                if(index == curr_index) {
                    // Update dictionary and bitlen used for encoding
                    update_dictionary(A, index);
                    curr_index = curr_index << 1;
                    curr_bit_len += 1;
                } 
                // Add the new charcter sequence to the dictionary
                add_in_dictionary(A, str, index);
                index++;
                
                // The charcater sequence except the last charcter will be 
                // present in the dictionary since curr state in NOT_IN_DICT
                
                for(i = 0; i < strlen(str) - 1; i++) {
                    temp[i] = str[i];   
                }
                temp[i] = '\0';
                
                // Write the value corresponding to key being referrred to
                // character sequence present in dictionary to compressed file 

                write_buffer(temp, fdc, curr_bit_len,'n');
                
                // Store the last character
                str[0] = str[strlen(str) - 1];
                str[1] = '\0';
                nextstate = IN_DICT;
                break;
        }
        currstate = nextstate;
    }
    // Last buffer also need to be written (if necessary)
    write_buffer(str, fdc, curr_bit_len,'l');
    //print_dictionary(*A, index);
}

/* This function writes the bit string corresponding to the  
 * key or the character sequence encoded by file and present 
 * in the dictionary.
 * Note - The bit lenghts being written in file can be varying  
 * thus the curr_bit_len paramter is passed to function. The 
 * extra character passed to the function to differentiate 
 * for the last call to the function.
 */

void write_buffer(char *key, int fd, int curr_bit_len,char ch) {
    int temp = 0;
    char str[MAX_SEQUENCE];
    static int bit_written = 0, BUFFER, index = 0;
    
    // Search the value corresponding to the key in the dictionary.
    temp = search_in_dictionary(key);
    // Get the binary representation of the value 
    get_bit_strings(str, temp, curr_bit_len);

    if(temp == -1) {
        printf("Can't write buff in file, error in creating the dictionary ...\n");
        exit(1);
    }
    while(bit_written < curr_bit_len) {
        for(;(bit_written < curr_bit_len) && (index < MAX_BUF); bit_written++, index++) {
            BUFFER = BUFFER << 1;
            if(str[bit_written] == '1') {
                BUFFER++;
            }
        }  
        if(index == MAX_BUF) {
            // If BUFFER is full write then clear it
            write(fd, &BUFFER, 1); 
            BUFFER = 0;
            index = 0;
        }
    }
    // For the last call shift the bits of BUFFER left
    // until BUFFER is not full
    if(ch == 'l' && index != MAX_BUF) {
        for(; index < MAX_BUF; index++) {
            BUFFER = BUFFER << 1;
        }
        write(fd, &BUFFER, 1);
    }
    bit_written = 0;
}

/* Given a decimal number, function gets the binary 
 * representation of the number in the string.
 */

void get_bit_strings(char str[],int num, int len) {
    int num_bits ,i, start, end;
    char temp;
    num_bits = log2(num) + 1;
    for(i = 0; i < num_bits; i++) {
        str[i] = (num & 01) + '0'; 
        num = num >> 1;
    }  
    while(i < len) {
        str[i] = '0';
        i++;
    }
    str[i] = '\0';
    start = 0;
    end = strlen(str) - 1;
    while(start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

