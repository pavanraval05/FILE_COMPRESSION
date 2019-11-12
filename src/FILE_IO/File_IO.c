#include"File_IO.h"

void open_file_read(int *fd, char *file_name) {
    
    *fd = open(file_name, O_RDONLY, S_IRUSR | S_IWUSR);
    if(*fd == -1) {
        printf("The filename is %s\n", file_name);
        perror("The error is - ");
        exit(errno);
    }
}

void open_file_write(int *fd, char *file_name) { 
    *fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(*fd == -1) {
        printf("The filename is %s\n", file_name);
        perror("The error is - ");
        exit(errno);
    }
}

int freadline(int fd, char *str) {    
    char ch;
    int i = 0;
    while((ch = read(fd, &ch, 1))) {
        if(ch != '\n') {
            str[i++] = ch;
        }
        else {
            break;
        }
    }
    str[i] = '\0';
    return (ch == 0) ? 0 : 1;
}

int freadchar(int fd, char *ch) {

    int i;
    i = read(fd, ch, 1);
    return (i == 0) ? 0 : i;
}

long int get_file_size(char *file_name) {
    
    struct stat statbuf;
    if(stat(file_name, &statbuf) != -1) {
        return statbuf.st_size;
    } 
    return -1;
}

char *get_file_chars(int fd, long int file_size) {
    char ch, *arr;
    long int index =0;
    arr = (char *)malloc(sizeof(char) * file_size);
    if(arr == NULL) {
        printf("Error in allocating space to store file\n");
        exit(errno);
    }
    else {
        while(freadchar(fd, &ch)) {
            arr[index++] = ch;
        }
    }
return arr;
}

/* Functions Checks if correct extension file is given for 
 * decompression .Reason the Function can only decode that 
 * particular file which were encoded for that entenstion
 */

void check_file_extention(char *file_name) {
    if(strstr(file_name, EXT) == NULL) {
        printf("The extiontion of the file is not supported for decompression ...\n");
        exit(1);
    }
}

/* Tokenizes the file_name to get output in correct
 * folder with correct file_name.
 */

void tokenize_file_name(char *ans, char *file_name) {
    int len, i, start, end;
    char temp, dummy[MAX] = {};

    len = strlen(file_name);
    len = len - strlen(EXT); 
    i = 0;
    while(len && file_name[len - 1] != '/') {
        ans[i++] = file_name[len - 1];
        len--;
    }
    ans[i] = '\0';
    
    start = 0;
    end = strlen(ans) - 1;

    while(start < end) {
        temp = ans[start];
        ans[start]  = ans[end];
        ans[end] = temp;
        start++;
        end--;
    }
    strcat(dummy, RESULTS);
    strcat(dummy, ans); 
    strcpy(ans, dummy);
}

