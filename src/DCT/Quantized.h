#ifndef QUANTIZED_H 
#define QUANTIZED_H 1

#include<stdio.h>
#include<stdlib.h>

#define DCT_FACTOR 8

int **get_matrix_int(int row, int col);

float **get_matrix_float(int row, int col);

void Quantize_Y(float temp[][DCT_FACTOR], int quant_output[][DCT_FACTOR]);

void Quantize_C(float temp[][DCT_FACTOR], int quant_output[][DCT_FACTOR]);

#endif


