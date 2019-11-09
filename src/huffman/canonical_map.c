#include "canonical_map.h"
#include"../FILE_IO/File_IO.h"

/* Prints the bits present in the BUFFER.
 */

void print_buffer(int num) {
    int arr[BUFSIZE];
    for(int i = 0; i < BUFSIZE; i++) {
        arr[BUFSIZE - i -1] = num & 01;
        num = num >> 1;
    }
    for(int i = 0; i < BUFSIZE; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

/* Finds the location of the character in
 * if present in the code_table.
 */

int search_codebook(codebook temp[], int num, char ch) {
    int i = -1;
    for(i = 0; i < num; i++) {
        if(temp[i].symbol == ch) {
            return i;
        }   
    }
    if(i == -1) {
        printf("There is problem - couldn't track in codebook\n");
        exit(1);
    }
    return -1;
}

/* Returns a codebook having num_symbols entries.
 */

codebook *get_codebook(int num_symbols) {
    codebook *temp;
    temp = (codebook *)malloc(sizeof(codebook) * num_symbols);
    if(temp == NULL) {
        perror("The error is :");
        exit(1);
    } 
    return temp;
}

/* Prints the codebook symbols abd bit_strings.
 */

void print_bit_strings(codebook *temp, int num) {
    printf("SYMBOLS\tFREQUENCY\n");
    for(int i = 0; i < num; i++) {
        printf("%d %s\n",temp[i].symbol, temp[i].str);  
    }
}

/* Functions maps the huffman generated codes to get cannoical 
 * codes . Mapping is based as sort the characters by bit-lenght,
 * then those having same bit lenght are again sorted on ASCII value.
 * 1. Now assign the first element all 0 in bit string having len 
 *    same as that of huffman code.
 * 2. If next symbol has the same bit lenght as that of previous then
 *    increment the previous bit-string and store.
 * 3. If next symbol has different bit lenght then increment previous 
 *    value and append 0 at the end untill the bit length becomes equal.
 * Repeate for all characters.
 */

codebook *map_bit_strings(codebook temp[], int num) {

    codebook *canonical_code;
    int i, j, len, digit;

    canonical_code = get_codebook(num);
    quick_sort(temp, 0, num-1, 'l'); 
    for(i = 0; i < num; i++) {
        canonical_code[i] = temp[i];
    }
    for(i = 0; i < num; i++) {
        for(j = i + 1; j < num; j++) {
            if(compare_by(canonical_code[i], canonical_code[j], 'l') != 0) {
                break;
            } 
        }
        quick_sort(canonical_code, i, j - 1, 's');
        i = j - 1;
    }    
    len = strlen(canonical_code[0].str);
    while(len) {
        canonical_code[0].str[len - 1] = '0'; 
        len--;
    }     
    for(i = 1; i < num; i++) {
        if(compare_by(canonical_code[i-1], canonical_code[i], 'l') == 0) {
            digit = convert_decimal(canonical_code[i-1].str);
            digit += 1;
            decimal_to_string(digit, canonical_code[i].str);
        }
        else {
            digit = convert_decimal(canonical_code[i-1].str); 
            digit += 1;
            convert_and_append(digit, canonical_code[i].str, strlen(canonical_code[i-1].str));
        }
    }   
    return canonical_code;
}

void convert_and_append(int num, char *str, int len) {
    int num_bits, i = 0, j = 0 , l;         
    num_bits = (int)log2(num) + 1;
    l = strlen(str);

    if(len != num_bits) {
        for(i = 0; len - num_bits - i > 0; i++) {
            str[i] = '0';
        }
    }
    for(j = 0; j < num_bits; j++) { 
        if(num & 01) {
            str[len - j - 1] = '1';
        } 
        else {
            str[len - j - 1] = '0'; 
        } 
        num = num >> 1;
    } 
    for(;len < l; len++) {
        str[len] = '0';
    }
    str[l] = '\0';
}

int convert_decimal(char *str) {
    int len, i, ans, pow = 1; 
    len = strlen(str);
    ans = 0;
    for(i = 0; i < len; i++) {
        ans += pow * (str[len - i - 1] - '0');  
        pow = 2 * pow;
    }
    return ans;
}

void decimal_to_string(int num, char *str) {
    int num_bits, i = 0, j = 0 ,len;         
    num_bits = (int)log2(num) + 1;
    
    len = strlen(str);
    if(len != num_bits) {
        for(i = 0; len - num_bits - i > 0; i++) {
            str[i] = '0';
        }
    }
    for(j = 0; j < num_bits; j++) { 
        if(num & 01) {
            str[len - j - 1] = '1';
        } 
        else {
            str[len - j - 1] = '0'; 
        } 
        num = num >> 1;
    } 
    str[len] = '\0';
}

/* Quick Sort Algorithm is implemented for sorting.
 */

void quick_sort(codebook a[],int l,int u, char ch) {
    int j;
    if(l < u)
    {
        j = partition(a, l, u, ch);
        quick_sort(a, l, j - 1, ch);
        quick_sort(a, j + 1, u, ch);
    }
}
int partition(codebook a[], int l, int u, char ch) {
    codebook v, temp;
    int i, j;
    v = a[l];
    i = l;
    j = u + 1;
    do {
        do {
            i++;
        } while(i <= u && compare_by(a[i], v, ch) > 0);

        do {
            j--;
        } while(compare_by(v , a[j], ch) > 0);

        if(i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    } while(i < j);

    a[l] = a[j];
    a[j] = v;

    return(j);
}

/* Compare function ,compares the two codebook 
 * values either by symbol or by len , depending 
 * upon the character argument passed to it.
 */

int compare_by(codebook a, codebook b, char ch) {
    if(ch == 's') {
        return (b.symbol - a.symbol);
    }
    else if(ch == 'l') {
        return (strlen(b.str) - strlen(a.str));
    }
    return 0;
}

