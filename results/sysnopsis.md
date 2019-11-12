## MIS - 111803172       
## Name - Kishan Patel
## Div - 2               
## Batch - S4

### PROJECT NAME
* FILE COMPRESSION ALGORITHMS -
    * **Huffman compression**
    * **LZW compression**
* * *

# Aim of the project -

* Implement above mentioned compression algorithms and analyze time complexity, compression ratio, file type on which algorithms work, etc 
* The task of decompression will also be done along with compression to get the original data back.
* Along with this the aim of project also to implement file compression algorithms involved for image file compression.

## Overview of the project -
* The compression algorithms are classified into mainly two types - 
    * Lossless compression 
    * Lossy compression

* *Lossless compression* involves compression of data in which no information is lost in the process of data compression. Examples are Huffman Algorithm , LZ77 , LZ78, LZW ,Arithmetic coding , etc.   

* *Lossy compression* involves compression of data in which some information is lost in the process of data compression. Examples are discrete Cosine transform , quantization, etc

## Huffman Compression Algorithm -

* Algorithm works by creating binary tree of nodes. The tree is created according to the frequency comparison of each character.
* Thus we can say that most repeating character is present near to the root node and the least repeating character will act as a leaf in the binary tree. 
* Thus we can say that each character has can be represented as a unique bit pattern and thus this bit pattern can be stored and resulting storage of bits will be the compressed form of the original data.
* Thus in order to decompress the data we need the tree to decode the data and get the original data back.
* In this process no information or set of data is lost thus Huffman coding comes under the category of lossless compression algorithm.

* functions required are - basic file I/O , sorting algorithms 
* DATA STRUCTURE TO BE USED - tree, heap, and priority queue etc. 

## LZW Algorithm - 

* Its is a Dynamic Dictionary technique. Algorithm is used when there are large phrases and sentences to decode. 
* It works on reading a sequence then grouping of symbols and grouping symbols into strings and converting string into codes.
* Make use of code table of suitable length and assign 0-255 indexes with the ASCII character set 
* Compression starts using code entries from 256 index.
* More the similarity in strings more is the compression. 
* Thus in this process a dictionary gets created for representing the sequence of the codes. Thus while decoding we make use of this dictionary to decompress the data back.
* High Compression ratio is obtained for large text files. 


## FURTHER TASK -
* Will try to implement DCT (Discrete Cosine Transformation) as a mean of lossy compression technique. This Algorithm is widely used in application based software like Whatsapp and also used in JPEG converters.


