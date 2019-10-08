#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

/* Contains the prototypes of the all the basic operations
 * required for the file input and output , examples 
 * readline , read a charachter, write line , write a 
 * character.
 */

void open_file_read(int *fd, char *file_name);

void open_file_write(int *fd, char *file_name);

int freadline(int fd, char *str);

int freadchar(int fd, char *ch);

long int get_file_size(char *file_name);

char *get_file_chars(int fd, long int file_size);

