#include<stdio.h>
#include<stdlib.h>
#define HEAP_CAPACITY 1024

typedef struct tree_elements {
    char ch;
    long int frequency;
} tree_elements;  


typedef struct priority_quee {
    tree_elements data; 
    struct priority_quee *left;
    struct priority_quee *right;
} priority_quee;

typedef struct heap {
    priority_quee tree[HEAP_CAPACITY]; 
    int index;
} heap;

void InitHeap(heap *h);

int isHeapFull(heap h);

int isHeapEmpty(heap h);

int isSizeOne(heap h);

int compare_freq(heap *h, int a, int b);

void Insert_minHeap(heap *h, priority_quee temp);

void swap(heap *h, int a, int b);

void printHeap(heap h);

priority_quee *Remove_minHeap(heap *h);

int smallest(heap *h, int parent, int child1, int child2);

void printHeap(heap h);

priority_quee *Create_sub_tree(heap *h);

/* Some other functions provided to write and read data form
 * the priority_quee and tree_elements ADTs
 */

priority_quee get_heap_element(char ch, long int frequency);

long int get_frequency(tree_elements *p, int index);

char get_character(tree_elements *p, int index);

void write_frequency(tree_elements *p, long int frequency);

void write_charachter(tree_elements *p, char ch);
