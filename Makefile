SRC=src
CALLER=caller
HUFFMAN=huffman
FILE_IO=FILE_IO

CFLAGS = -Wall -g
MFLAGS = -lm
CC = gcc

FLAGS = -fsanitize=address -std=c99 $(CFLAGS) 

SOURCE = 	$(SRC)/main.c\
	$(SRC)/$(HUFFMAN)/huffman_compression.c\
	$(SRC)/$(FILE_IO)/File_IO.c\
	$(SRC)/$(CALLER)/caller.c

OBJECT = $(SOURCE:.c=.o)

run: $(OBJECT) 
	$(CC) $(FLAGS) $(OBJECT) -o kishan 

$(OBJECT) : %.o : %.c Makefile
	$(CC) $(FLAGS) -c  $< -o $@

clean:
	$(RM) $(SRC)/*.o kishan $(SRC)/$(CALLER)/*.o $(SRC)/$(HUFFMAN)/*.o $(SRC)/$(FILE_IO)/*.o


