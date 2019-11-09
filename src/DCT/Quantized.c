#include "Quantized.h"

int Quantization_Y[DCT_FACTOR][DCT_FACTOR] = {
        {16, 11 ,10 ,16 ,124, 140, 151, 161 }, 
        {12, 12 ,14 ,19 ,126, 158, 160, 155 }, 
        {14, 13 ,16 ,24 ,140, 157, 169, 156 }, 
        {14, 17 ,22 ,29 ,151, 187, 180, 162 }, 
        {18, 22 ,37 ,56 ,168, 109, 103, 177 }, 
        {24, 35 ,55 ,64 ,181, 104, 113, 192 }, 
        {49, 64 ,78 ,87 ,103, 121, 120, 101 }, 
        {72, 92 ,95 ,98 ,112, 100, 103, 199 }
};

int Quantization_C[DCT_FACTOR][DCT_FACTOR] = {
        {17, 18, 24, 47, 99, 99, 99, 99}, 
        {18, 21, 26, 66, 99, 99, 99, 99}, 
        {24, 26, 56, 99, 99, 99, 99, 99}, 
        {47, 66, 99, 99, 99, 99, 99, 99}, 
        {99, 99, 99, 99, 99, 99, 99, 99}, 
        {99, 99, 99, 99, 99, 99, 99, 99}, 
        {99, 99, 99, 99, 99, 99, 99, 99}, 
        {99, 99, 99, 99, 99, 99, 99, 99} 
};


int **get_matrix_int(int row, int col) {
    int **temp = NULL, i;
    temp = (int **)calloc(row , sizeof(int *));
    if(temp == NULL) {
        perror("The error is:");
        exit(1);
    }
    for(i = 0; i < row; i++) {
        temp[i] = (int *)calloc(col ,sizeof(int));  
        if(temp[i] == NULL) {
            perror("The error is:");
            exit(1);
        }
    }
    return temp;
}

float **get_matrix_float(int row, int col) {
    float **temp = NULL;
    int i = 0;
    temp = (float **)calloc(row, sizeof(float *));
    if(temp == NULL) {
        perror("The error is:");
        exit(1);
    }
    for(i = 0; i < row; i++) {
        temp[i] = (float *)calloc(col, sizeof(float));  
        if(temp[i] == NULL) {
            perror("The error is:");
            exit(1);
        }
    }
    return temp;
}

void Quantize_Y(float temp[][DCT_FACTOR], int quant_output[][DCT_FACTOR]) {
    int i, j;
    for(i = 0; i < DCT_FACTOR; i++) {
        for(j = 0; j < DCT_FACTOR; j++) {
            quant_output[i][j] = (int)temp[i][j] / Quantization_Y[i][j];
        }
    }
}

void Quantize_C(float temp[][DCT_FACTOR], int quant_output[][DCT_FACTOR]) {
    int i, j;
    for(i = 0; i < DCT_FACTOR; i++) {
        for(j = 0; j < DCT_FACTOR; j++) {
            quant_output[i][j] = (int)temp[i][j] / Quantization_C[i][j];
        }
    }
} 


