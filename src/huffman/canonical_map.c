#include "canonical_map.h"
#include"../FILE_IO/File_IO.h"

void encode_file(codebook canonical_code[], int num_symbols, char *file_name) {
    uint8_t BUFFER;
    int fd, fdc, index = 0, bit_string_index = 0, pos, cur_state, next_state, len, x;
    char ch, str[MAX_BITS];

    open_file_read(&fd, file_name);
    strcat(file_name,".kishan");
    open_file_write(&fdc, file_name);
    
    cur_state = START;
    bit_string_index = 0;
    index = 0;
    BUFFER = 0;
    
    while(cur_state != END) {
        switch(cur_state) {
            case START:
                if(freadchar(fd, &ch) != 0) {
                    pos = search_codebook(canonical_code, num_symbols, ch); 
                    strcpy(str, canonical_code[pos].str);
                    len = strlen(str);
                    if(len - index < BUFSIZE) {
                        next_state = ENOUGH_BUF_SPACE;
                    }
                    else if (len - index > BUFSIZE) {
                        next_state = NOT_ENOUGH_BUF_SPACE; 
                    }
                    else {
                        next_state = PREFECT_BUF_SPACE;
                    }
                }
                else {
                    next_state = END;
                }
                break;
            case PREFECT_BUF_SPACE:
                for(;bit_string_index < strlen(str); bit_string_index++) {
                    x = str[bit_string_index] - '0';        
                    BUFFER = BUFFER << 1;
                    BUFFER |= x;
                }
                write(fdc, &BUFFER, 1);
                print_buffer(BUFFER);

                index = 0;
                bit_string_index = 0;
                if(freadchar(fd, &ch) != 0) {
                    pos = search_codebook(canonical_code, num_symbols, ch); 
                    strcpy(str, canonical_code[pos].str);
                    len = strlen(str);
                    if(len - index < BUFSIZE) {
                        next_state = ENOUGH_BUF_SPACE;
                    }
                    else if (len - index > BUFSIZE) {
                        next_state = NOT_ENOUGH_BUF_SPACE; 
                    }
                    else {
                        next_state = PREFECT_BUF_SPACE;
                    }
                }
                else {
                    next_state = END;
                }
                break;
            case ENOUGH_BUF_SPACE:
                for(;bit_string_index < strlen(str); bit_string_index++, index++) {
                    x = str[bit_string_index] - '0';
                    BUFFER = BUFFER << 1;
                    BUFFER |= x;
                }
                if(freadchar(fd, &ch) != 0) {
                    bit_string_index = 0;
                    pos = search_codebook(canonical_code, num_symbols, ch); 
                    strcpy(str, canonical_code[pos].str);
                    len = strlen(str);
                    if(len + index < BUFSIZE) {
                        next_state = ENOUGH_BUF_SPACE;
                    }
                    else if (len + index > BUFSIZE) {
                        next_state = NOT_ENOUGH_BUF_SPACE; 
                    }
                    else {
                        next_state = PREFECT_BUF_SPACE;
                    }
                }
                else {
                    for(;index < BUFSIZE; index++) {
                        BUFFER = BUFFER << 1;
                        BUFFER |= 1;
                    }
                    write(fdc, &BUFFER, 1);
                    print_buffer(BUFFER); 
                    next_state = END;
                }
                break;
            case NOT_ENOUGH_BUF_SPACE:
                for(; index < BUFSIZE; index++) {
                    x = str[bit_string_index] - '0';
                    BUFFER = BUFFER << 1;
                    BUFFER |= x; 
                    bit_string_index++;
                }
                write(fdc, &BUFFER, 1); 
                print_buffer(BUFFER); 
                index = 0;
                BUFFER = 0;
                len = strlen(str);
                if(len - bit_string_index < BUFSIZE) {
                    next_state = ENOUGH_BUF_SPACE;
                }
                else if(len - bit_string_index > BUFSIZE) {
                    next_state = NOT_ENOUGH_BUF_SPACE;
                } 
                else {
                    next_state = PREFECT_BUF_SPACE;
                }
                break; 
        }
        cur_state = next_state;
    }
       
}

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


int search_codebook(codebook temp[], int num, char ch) {
    int i;
    for(i = 0; i < num; i++) {
        if(temp[i].symbol == ch) {
            return i;
        }   
    }
    return -1;
}

codebook *get_codebook(int num_symbols) {
    codebook *temp;
    temp = (codebook *)malloc(sizeof(codebook) * num_symbols);
    if(temp == NULL) {
        perror("The error is :");
        exit(1);
    } 
    return temp;
}

void print_bit_strings(codebook *temp, int num) {
    printf("SYMBOLS\tFREQUENCY\n");
    for(int i = 0; i < num; i++) {
        printf("%d %s\n",temp[i].symbol, temp[i].str);  
    }
}

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
            convert_and_append(digit, canonical_code[i].str);
        }
    }  
    return canonical_code;
}

void convert_and_append(int num, char *str) {
    int len, num_bits, i;
    len = strlen(str);
    num_bits = (int)log2(num) + 1;
    for(i = 0; i < num_bits; i++) {
        if(num & 01) {
            str[num_bits - i - 1] = '1';  
        }
        else {
            str[num_bits - i - 1] = '0';  
        }
        num = num >> 1;
    } 
    for(; i < len; i++) {
        str[i] = '0';
    }
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

void quick_sort(codebook a[],int l,int u, char ch) {
    int j;
    if(l<u)
    {
        j = partition(a, l, u, ch);
        quick_sort(a, l, j - 1, ch);
        quick_sort(a, j + 1, u, ch);
    }
}

int partition(codebook a[],int l,int u, char ch) {
    codebook v, temp;
    int i, j;
    v = a[l];
    i = l;
    j = u + 1;
    do
    {
        do {
            i++;
        } while(compare_by(a[i], v, ch) > 0 && i <= u);

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

int compare_by(codebook a, codebook b, char ch) {
    if(ch == 's') {
        return (b.symbol - a.symbol);
    }
    else if(ch == 'l') {
        return (strlen(b.str) - strlen(a.str));
    }
    return 0;
}
