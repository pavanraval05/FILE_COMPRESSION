### PROJECT
* FILE COMPRESSION ALGORITHMS -
    * **Huffman compression**
    * **LZW compression**
    * **DCT**
* * *

### Aim of the project -

* Implement above mentioned compression algorithms and analyze time complexity, compression ratio, file type on which algorithms work, etc 
* The task of decompression will also be done along with compression to get the original data back.
* Along with this the aim of project also to implement file compression algorithms involved for image file compression.
  (Discrete Cosine tranform)

### Usage of the code -

* >> ./kishan -[options] file-name.
* The options are -c for compression and -d for decompression.
* The next sequence tells which algo to implement for the options taken.
* h : huffman compression algorithm.
* l : LZW. 
* i : DCT (for image compression only).
* example - >> ./kishan -ch file.txt 
               (This tells to compress the file using huffman encoding)
            >> ./kishan -dl file.txt.kp
                (This tells to decompress the file using LZW algorithm) NOTE - Should only give files with .kp extension

