#ifndef DCT_DECOMPRESSION_H
#define DCT_DECOMPRESSION_H 1

#include "Quantized.h"

void decompress_by_DCT(char *file_name);

void Apply_inverse_DCT(int fdd,int row, int col);

void Follow_reverse_steps(int fdd, int row, int col, int **Y, int **Cb, int **Cr, int **Y_ans, int **Cb_ans, int **Cr_ans);

void Inverse_Cosine_tranform(int arr[][DCT_FACTOR], int temp[][DCT_FACTOR]);
#endif
