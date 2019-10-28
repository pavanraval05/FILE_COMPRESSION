#ifndef DICTIONARY_H
#define DICTIONARY_H 1

#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define NUM_CHARS 256
#define MAX_SEQUENCE 128

#define BIT_LEN 12
#define DICT_SIZE ((2 << BIT_LEN) - 1)

typedef struct dictionary {
    int value;
    char key[MAX_SEQUENCE];
} dictionary;

typedef ENTRY data;

typedef dictionary *DICT;

void initialize_dictionary(DICT *A, int size);

void add_in_dictionary(DICT *A, char *key, int index);

int search_in_dictionary(char *key);

void print_dictionary(DICT A, int size);

void create_hash_table(int max_size);

void initialize_hash_table();

int search_in_hash_table(char *key);

void add_in_hash_table(char *key , int value);

#endif
