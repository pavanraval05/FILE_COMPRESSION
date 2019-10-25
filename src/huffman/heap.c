#include"heap.h"

/* Initializing the parent of heap to 
 * zero baiscally empty heap
 */

void InitHeap(heap *h, int HEAP_CAPACITY) {
    h->tree = (priority_quee **)malloc(sizeof(priority_quee *) * HEAP_CAPACITY);
    h->index = 0;
    h->end = HEAP_CAPACITY;
}

/* Checks if the heap is full or not
 */

int isHeapFull(heap h) {
    if(h.index == h.end) {
        return 1;
    }
    return 0;
}

/* Checks if the heap is Empty or not
 */

int isHeapEmpty(heap h) {
    if(h.index == 0) {
        return 1;
    }
    return 0;
}

/* Checks if the heap has only one element
 * or not.
 */

int isSizeOne(heap h) {
    if(h.index == 1) {
        return 1;
    }
    return 0;
}
/* Compares two heap elements based on the frequency
 * heap element contains - character and frequency
 * returns 1 if index a has high frequency  
 * returns -1 if index b has high frequency
 */

int compare_freq(heap *h, int a, int b) {
    if(h->tree[a]->data.frequency > h->tree[b]->data.frequency) {
        return 1;
    }
    return -1;
}

/* Inserts a element in the minHeap
 * Note the property of minHeap is maintained
 */

void Insert_minHeap(heap *h, priority_quee temp) {
    int children, parent;
    h->tree[h->index] = (priority_quee *)malloc(sizeof(priority_quee));  
    *(h->tree[h->index]) = temp;

    children = h->index;
    parent = (children-1)/2;
    while(children > 0) {
        if(compare_freq(h, parent, children) > 0) {
            swap(h, children, parent);
            children = parent;
            parent = (children - 1)/2; 
        }
        else {
            break;
        }
    }
    (h->index)++;
} 

/* Swaps the Heap elements having index a and b.
 * Swaps the elements in the heap array. 
 */

void swap(heap *h, int a, int b) {
    priority_quee *temp;
    temp = h->tree[a];
    h->tree[a] = h->tree[b];
    h->tree[b] = temp;
}

/* Removes and returns the root element of the minheap 
 * Note that minheap property is not changed 
 * (Always returns the pointer to minimum element from the heap)
 */

priority_quee* Remove_minHeap(heap *h) {

    int child1, child2, parent, min_index; 
    priority_quee *temp;

    temp = h->tree[0]; 
    h->tree[0] = h->tree[h->index-1];
    (h->index)--; 
    
    parent = 0;
    child1 = 2 * parent + 1;
    child2 = 2 * parent + 2;

    while(child1 < h->index) {
        min_index = smallest(h, parent , child1, child2);
        if(min_index != parent) {
            swap(h, min_index, parent);
            parent = min_index;
            child1 = 2 * parent + 1; 
            child2 = 2 * parent + 2;
        }       
        else {
            break;
        }
    }   
    return temp;
}

/* Finds the element containing least frequency from 
 * the index of respective elements passed as arguments
 * Note function returns the index of the smallest element
 * and the values of contained by that element
 */

int smallest(heap *h, int parent, int child1, int child2) {
    if(compare_freq(h, parent, child1) < 0) {
        if(compare_freq(h, parent, child2) < 0) {
            return parent; 
        }
        else {
            return child2;
        }
    } 
    else {
        if(compare_freq(h, child1 , child2) < 0) {
            return child1;
        }
        else {
            return child2;
        }
    }
}

/* Prints all the elements of the heap
 */

void printHeap(heap h) {
    for(int i = 0; i < h.index; i++) {
        printf("%d %ld\t",h.tree[i]->data.ch, h.tree[i]->data.frequency);
    }
    printf("\n");
}

/* Destroys the heap data structure
 * Frees all the memory allocated.
 */

void destroyHeap(heap *h) {
    free(h->tree); 
    return;
}

/* GIVEN BELOW FUNCTIONS PROVIDE THE ACCESS TO 
 * CHANGE THE DATA IN ADTs - tree_elements and priority_quee.
 */

/* Checks if it is the leaf node or not
 */

int IsLeaf(priority_quee temp) {
    return (!temp.left && !temp.right);
}

/* Deletes the priority quee hierarchy 
 * created for huffman encoding.
 */

void remove_priority_quee(priority_quee *ptr) {
    if(ptr == NULL) {
        return;
    }
    else {
        remove_priority_quee(ptr->left);
        remove_priority_quee(ptr->right);
        free(ptr);
    }
}

/* Traverses the quee(heap) and prints the data in 
 * preorder manner (root -> left child -> right child).
 */

void traverse_priority_quee(priority_quee *node) {
    if(node == NULL) {
        return;
    }
    else {
        printf("%d %ld\t",node->data.ch, node->data.frequency);
        traverse_priority_quee(node->left);
        traverse_priority_quee(node->right);
    }
}


/* Creates a subtree and returns a priority_quee variable
 * containg the left and right child passed as pointer
 * arguments. (note left node values will always be minimum)     
 */

priority_quee Create_subtree(priority_quee *ptr1, priority_quee *ptr2) {
    priority_quee node;
    node.left = ptr1;
    node.right = ptr2;
    node.data.frequency = ptr1->data.frequency + ptr2->data.frequency;
    node.data.ch = EOF;
    return node;     
}

/* Functions returns a heap element given character
 * and frequency as argument.
 */

priority_quee get_heap_element(char c, long int f) {
    priority_quee temp;
    temp.data.ch = c;
    temp.data.frequency = f;
    temp.left = temp.right = NULL;
    return temp;
}

/* Gets the priority_quee variable frequency
 */

long int get_quee_frequency(priority_quee temp) {
    return temp.data.frequency;
}

/* Gets the priority_quee variable character
 */

char get_quee_character(priority_quee temp) {
    return temp.data.ch;
} 

/* Gets the frequency of the tree_element at index 
 * passed as a argument.
 */

long int get_frequency(tree_elements *p, int index) {
    if(index < 0) {
        return -1;
    }
    return p[index].frequency;
}

/* Gets the character of the tree_element at index
 * passed as a argument.
 */

char get_character(tree_elements *p, int index) {
    if(index < 0) {
        return -1;
    }
    return p[index].ch;
}

/* Writes frequency in the tree_element variable 
 * passed as a argument.
 */

void write_frequency(tree_elements *p, long int f) {
    (*p).frequency = f;
}

/* Writes character in the tree_element variable 
 * passed as a argument.
 */

void write_charachter(tree_elements *p, char c) {
    (*p).ch = c; 
}
