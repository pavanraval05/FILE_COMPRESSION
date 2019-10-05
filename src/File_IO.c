#include"File_IO.h"

void open_file_read(int *fd, char *file_name) {
    
    *fd = open(file_name, O_RDONLY, S_IRUSR | S_IWUSR);
    if(*fd == -1) {
        perror("The error is - ");
        exit(errno);
    }
}

void open_file_write(int *fd, char *file_name) {
    
    *fd = open(file_name, O_WRONLY, S_IRUSR | S_IWUSR);
    if(*fd == -1) {
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
    return (i == 0) ? 0 : 1;
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

