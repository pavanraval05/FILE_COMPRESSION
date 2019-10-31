#include "LZW_compression.h"
#include "../FILE_IO/File_IO.h"

void compress_by_LZW(char *file_name) {
    DICT A;  
    initialize_dictionary(&A, DICT_SIZE);
    encode_file_LZW(&A, file_name);
}

void encode_file_LZW(DICT *A,char *file_name) {
    int fd, fdc, currstate, nextstate, index, i;
    char ch, str[MAX_SEQUENCE], temp[MAX_SEQUENCE];

    open_file_read(&fd, file_name); 
    strcat(file_name, EXT);
    open_file_write(&fdc, file_name);
    
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
                write_buffer(temp, fdc);
                index++;
                str[0] = str[strlen(str) - 1];
                str[1] = '\0';
                nextstate = IN_DICT;
                break;
        }
        currstate = nextstate;
    }
    write_buffer(str, fdc);
    print_dictionary(*A, index);
}

void write_buffer(char *key, int fd) {
    int temp = 0;
    char str[MAX_SEQUENCE];
    static int bit_written = 0, curr_bit_len = BIT_LEN, BUFFER, index = 0;
    
    temp = search_in_dictionary(key);
    get_bit_strings(str, temp, curr_bit_len);
    
    printf("value and its bitstring - %d %s\n",temp, str);
    
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
            write(fd, &BUFFER, 1); 
            print_buff(BUFFER, 8);
            BUFFER = 0;
            index = 0;
        }
    }
    bit_written = 0;
}
    
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

