#include "dictionary.h"

void initialize_dictionary(DICT *A, int size) {
    dictionary *temp;
    int i;
    temp = (dictionary *)malloc(sizeof(dictionary) * size);
    if(temp == NULL) {
        perror("The error is"); 
        exit(1);
    } 
    for(i = 0; i < NUM_CHARS; i++) {
        temp[i].value = i;
        temp[i].key[0] = (char)i; 
        temp[i].key[1] = '\0';
    }
    (*A) = temp;
    create_hash_table(DICT_SIZE * (1.25));
    initialize_hash_table();
}

void add_in_dictionary(DICT *A, char *key, int index) {
    dictionary temp;    
    strcpy(temp.key, key);
    temp.value = index;
    (*A)[index] = temp;
    add_in_hash_table(key, index); 
}

int search_in_dictionary(char *key) {
    return search_in_hash_table(key);
}

void print_dictionary(DICT A, int size) {
    int i = 0;
    printf("DICTIONARY has size %d\nINDEX\tKEY\n",size);
    for(i = NUM_CHARS; i < size; i++) {
        printf("%d %s\n", A[i].value, A[i].key); 
    }
}

void create_hash_table(int max_size) {
    if(hcreate(max_size) == 0) {
        fprintf(stderr, "There is a error in creating a hash table\n");
        exit(1);
    }
}

void initialize_hash_table() {
    char key[MAX_SEQUENCE];
    int i;
    for(i = 0; i < NUM_CHARS; i++) {
        sprintf(key,"%c",(char)i); 
        add_in_hash_table(key, i); 
    }
}

int search_in_hash_table(char *key) {
    data *ptr, temp;
    temp.key = key;
    
    ptr = hsearch(temp, FIND);
    if(ptr == NULL) {
        return -1;
    }
    else {
        return atoi((char *)ptr->data);
    }
}

void add_in_hash_table(char *key , int num) {
    data temp;
    char value[MAX_SEQUENCE];
    sprintf(value, "%d", num);
    temp.data = (char *)malloc(sizeof(char) * (strlen(value) + 1));
    temp.key = (char *)malloc(sizeof(char) * (strlen(key) + 1));

    strcpy(temp.data, value);
    strcpy(temp.key, key);
    hsearch(temp, ENTER);
}

void print_buff(int num, int len) {
    int arr[len];
    for(int i = 0; i < len; i++) {
        arr[len - i -1] = num & 01;
        num = num >> 1;
    }
    for(int i = 0; i < len; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

