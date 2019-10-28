#include "LZW_compression.h"
#include "../FILE_IO/File_IO.h"

void compress_by_LZW(char *file_name) {
    DICT A;  

    initialize_dictionary(&A, DICT_SIZE);

    encode_file_LZW(&A, file_name);
}

void encode_file_LZW(DICT *A,char *file_name) {
    int fd, currstate, nextstate, index, i;
    char ch, str[MAX_SEQUENCE], temp[MAX_SEQUENCE];
    
    open_file_read(&fd, file_name);
    currstate = START;        
    index = ASCII_CHARS;  
    
    while(currstate != STOP) {
        switch(currstate) {
            case START:
                if(freadchar(fd, &ch) != 0) {
                    str[0] = ch;
                    str[1] = '\0';
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
                add_in_dictionary(A, str, index);
                for(i = 0; i < strlen(str) - 1; i++) {
                    temp[i] = str[i];   
                }
                temp[i] = '\0';
                write_buffer(temp);
                index++;
                str[0] = str[strlen(str) - 1];
                str[1] = '\0';
                nextstate = IN_DICT;
                break;
        }
        currstate = nextstate;
    }
    print_dictionary(*A, index);
}

void write_buffer(char *key, int fd) {
    int temp = 0;
    temp = search_in_dictionary(key);
    if(temp == -1) {
        printf("Can't write buff in file, error in creating the dictionary ...\n");
        exit(1);
    }
    while(c_state != STOP) {
        switch(c_state) {
            case START:
                for(int i = 0; i < WRITE_BUFFER; i++) {
                    BUFFER |= (temp & 01);
                    temp = temp >> 1;
                    BUFFER = BUFFER << 1;
                }
                write(fd, &BUFFER, 1);
                BUFFER = 0;
                index = 0;
                for(int i = 0; i < current_bit_len - WRITE_BUFFER; i++) {
                    BUFFER |= (temp & 01);
                    temp = temp >> 1;
                    BUFFER = BUFFER << 1;
                    index++;
                }
                nextstate = HOLD_BUFFER;
                break;
            case WRITE_BUFFER:
                break;
            case HOLD_BUFFER:

                break;
        } 
        c_state = n_state;
    } 
}



