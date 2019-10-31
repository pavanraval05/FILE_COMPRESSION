#include<stdio.h>
#include<stdlib.h>
#include "dictionary.h"

#define READ_BUF 8

void decompress_by_LZW(char *file_name);

int convert_string_to_decimal(char *str);

void decode_file_LZW(char *file_name, DICT A);

