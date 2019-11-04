#include "LZW_compression.h"
#include "../FILE_IO/File_IO.h"

void compress_by_LZW(char *file_name) {
    DICT A;  
    initialize_dictionary(&A, DICT_SIZE);
    encode_file_LZW(&A, file_name);
}

void encode_file_LZW(DICT *A,char *file_name) {
    int fd, fdc, currstate, nextstate, index, i, curr_index, curr_bit_len;
    char ch, str[MAX_SEQUENCE], temp[MAX_SEQUENCE];

    open_file_read(&fd, file_name); 
    strcat(file_name, EXT);
    open_file_write(&fdc, file_name);

    currstate = START;        
    index = ASCII_CHARS;  
    curr_bit_len = BIT_LEN;
    curr_index = DICT_SIZE; 
    printf("DICT SZIE is %d and BIT is %d\n", DICT_SIZE, BIT_LEN);

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
                    if(ch == '\0') {
                        // To do something.
                        // This is for binary files.
                    }
                    else {
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
                }
                else {
                    nextstate = STOP;
                }
                break;
            case NOT_IN_DICT:
                if(index == curr_index) {
                    printf("Update curr bit len = %d and curr_index = %d \n", curr_bit_len , curr_index);
                    update_dictionary(A, index);
                    curr_index = curr_index << 1;
                    curr_bit_len += 1;
                } 
                printf("The value added in dictionary is %s at the index %d\n", str, index);
                add_in_dictionary(A, str, index);
                index++;
                for(i = 0; i < strlen(str) - 1; i++) {
                    temp[i] = str[i];   
                }
                temp[i] = '\0';
                write_buffer(temp, fdc, curr_bit_len,'n');
                str[0] = str[strlen(str) - 1];
                str[1] = '\0';
                nextstate = IN_DICT;
                break;
        }
        currstate = nextstate;
    }
    write_buffer(str, fdc, curr_bit_len,'l');
    print_dictionary(*A, index);
}

void write_buffer(char *key, int fd, int curr_bit_len,char ch) {
    int temp = 0, i;
    char str[MAX_SEQUENCE];
    static int bit_written = 0, BUFFER, index = 0;

    temp = search_in_dictionary(key);
    if(strlen(key) != 0) {
        get_bit_strings(str, temp, curr_bit_len);
    }
    else {
        for(i = 0; i < curr_bit_len; i++) {
            str[i] = '0';
        } 
        str[curr_bit_len] = '\0';
        temp = 0;
    }

    printf("key is %s\nvalue and its bitstring and current bitlenght - %d %s %d\n", key, temp, str, curr_bit_len);

    if(temp == -1) {
        printf("Can't write buff in file, error in creating the dictionary ...\n");
        exit(1);
    }
    printf("bits written - %d and index %d\n",bit_written, index);
    while(bit_written < curr_bit_len) {
        for(;(bit_written < curr_bit_len) && (index < MAX_BUF); bit_written++, index++) {
            //printf("index - %d\n",index);
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
    if(ch == 'l' && index != MAX_BUF) {
        printf("Last call\n");
        for(; index < MAX_BUF; index++) {
            BUFFER = BUFFER << 1;
        }
        write(fd, &BUFFER, 1);
        print_buff(BUFFER, 8);
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

