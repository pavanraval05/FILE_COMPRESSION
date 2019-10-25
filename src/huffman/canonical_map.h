#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<inttypes.h>

#define EXT ".kp"

#define BUFSIZE 8
#define MAX_BITS 256

#define START 100
#define PREFECT_BUF_SPACE 200
#define ENOUGH_BUF_SPACE 300
#define NOT_ENOUGH_BUF_SPACE 400
#define END 500

typedef struct codebook {
    char symbol;
    char str[MAX_BITS];
} codebook;

codebook *get_codebook(int num_symbols);

void print_bit_strings(codebook *temp, int num);

codebook *map_bit_strings(codebook temp[], int num);

void quick_sort(codebook a[],int l,int u, char ch);

int compare_by(codebook a, codebook b, char ch);

int partition(codebook a[],int l,int u, char ch);

int convert_decimal(char *str);

void decimal_to_string(int num, char *str);

void convert_and_append(int num, char *str, int l);

void encode_file(codebook canonical_code[], int num_symbols, char *file_name);

int search_codebook(codebook temp[], int num, char ch);

void print_buffer(int num);


