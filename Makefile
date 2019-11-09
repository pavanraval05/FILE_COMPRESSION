SRC=src
CALLER=caller
HUFFMAN=huffman
LZW=LZW
DCT=DCT
FILE_IO=FILE_IO


CFLAGS = -Wall -g
MFLAGS = -lm
CC = gcc
SEV = -fsanitize=address 

FLAGS = -std=c99 $(CFLAGS) 

SOURCE = 	$(SRC)/main.c\
	$(SRC)/$(HUFFMAN)/heap.c\
	$(SRC)/$(HUFFMAN)/canonical_map.c\
	$(SRC)/$(HUFFMAN)/huffman_compression.c\
	$(SRC)/$(HUFFMAN)/huffman_decompression.c\
	$(SRC)/$(LZW)/LZW_compression.c\
	$(SRC)/$(LZW)/LZW_decompression.c\
	$(SRC)/$(LZW)/dictionary.c\
	$(SRC)/$(DCT)/DCT_compression.c\
	$(SRC)/$(DCT)/Quantized.c\
	$(SRC)/$(FILE_IO)/File_IO.c\
	$(SRC)/$(CALLER)/caller.c

OBJECT = $(SOURCE:.c=.o)
	
run: $(OBJECT)
	$(CC) $(FLAGS) $(OBJECT) $(MFLAGS) -o kishan 

$(OBJECT) : %.o : %.c Makefile
	$(CC) $(FLAGS) -c  $< -o $@

clean:
	$(RM) $(SRC)/*.o $(SRC)/$(CALLER)/*.o $(SRC)/$(HUFFMAN)/*.o $(SRC)/$(LZW)/*.o $(SRC)/$(DCT)/*.o $(SRC)/$(FILE_IO)/*.o


