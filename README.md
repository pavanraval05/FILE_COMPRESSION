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
* example - >> ./pavan -ch file.txt 
               (This tells to compress the file using huffman encoding)
            >> ./kishan -dl file.txt.kp
                (This tells to decompress the file using LZW algorithm) NOTE - Should only give files with .kp extension

## Some important points to note - 

* The algorithms huffman and LZW implemented work only for text files. However huffman might work in binary files like PDF of GIF formats. However compression may not be achieved in such files.

* LZW is restricted upto 20kb text file.

* DCT algorithm needs to only .bmp files , reason is it is very difficult to read file formats in jpeg or jpg or even png
  file formats. BMP files are easily readable with langauge like C without any external library.

