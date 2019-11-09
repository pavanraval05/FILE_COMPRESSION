#ifndef DCT_COMPRESSION_H
#define DCT_COMPRESSION_H 1

#include<math.h>
#define pi 3.142857
#define DUMMY "dummy.txt"
#define DCT_FACTOR 8

void compress_by_DCT(char *file_name);

void get_height_width(char *file_name, int *height, int *width);

void readBMP(char* file_name, int **Y_Pixel, int **Cb_Pixel, int **Cr_Pixel);

void Apply_DCT(int width, int height, int **Y_Pixel, int **Cb_Pixel, int **Cr_Pixel, int **Y_ans, int **Cb_ans, int **Cr_ans);

void Cosine_tranform(int arr[][DCT_FACTOR], float temp[][DCT_FACTOR]);

void copy_sub_matrix(int i, int j, int **arr, int temp[][DCT_FACTOR]);

void exract_sub_matrix(int i, int j, int **arr, int temp[][DCT_FACTOR]);

void Cosine_tranform(int arr[][DCT_FACTOR], float temp[][DCT_FACTOR]);

void write_in_file(int row, int col, int **arrY, int **arrCb, int **arrCr);
#endif
