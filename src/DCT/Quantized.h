#ifndef QUANTIZED_H 
#define QUANTIZED_H 1

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define DUMMY "/home/kishan/dsa_project_111803172/dummy.txt"

#define DCT_FACTOR 8
#define pi (3.1415926535897932384626433279) 

int **get_matrix_int(int row, int col);

float **get_matrix_float(int row, int col);

void Quantize_Y(float temp[][DCT_FACTOR], int quant_output[][DCT_FACTOR]);

void Quantize_C(float temp[][DCT_FACTOR], int quant_output[][DCT_FACTOR]);

void copy_sub_matrix(int i, int j, int **arr, int temp[][DCT_FACTOR]);

void exract_sub_matrix(int i, int j, int **arr, int temp[][DCT_FACTOR]);

void DeQuantize_Y(int temp[][DCT_FACTOR]);

void DeQuantize_C(int temp[][DCT_FACTOR]);

#endif


