#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H 1

#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "dictionary.h"


#define ASCII_CHARS 256
#define MAX_BUF 8

#define START 100
#define IN_DICT 200
#define NOT_IN_DICT 300
#define STOP 400

void compress_by_LZW(char *file_name);

void encode_file_LZW(DICT *A, char *file_name);

void write_buffer(char *key, int fd);

void get_bit_strings(char str[],int num, int len);

#endif
