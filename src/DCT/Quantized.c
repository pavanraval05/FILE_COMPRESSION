#include "Quantized.h"

const int Q_Y[DCT_FACTOR][DCT_FACTOR] = {
    {16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 82},
    {18, 22, 37, 56, 68, 109, 103, 77},
    {24, 35, 55, 64, 81, 104, 113, 92},
    {49, 64, 78, 87, 103, 121, 120, 101},
    {72, 92, 95, 98, 112, 100, 103, 99} 
};

const int Q_C[DCT_FACTOR][DCT_FACTOR] = {
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
            quant_output[i][j] = (int)round(temp[i][j] / Q_Y[i][j]);
        }
    }
}

void Quantize_C(float temp[][DCT_FACTOR], int quant_output[][DCT_FACTOR]) {
    int i, j;
    for(i = 0; i < DCT_FACTOR; i++) {
        for(j = 0; j < DCT_FACTOR; j++) {
            quant_output[i][j] = (int)round(temp[i][j] / Q_C[i][j]);
        }
    }
} 

void DeQuantize_Y(int temp[][DCT_FACTOR]) {
    int i, j;
    for(i = 0; i < DCT_FACTOR; i++) {
        for(j = 0; j < DCT_FACTOR; j++) {
            temp[i][j] = temp[i][j] * Q_Y[i][j];
        }
    }
}

void DeQuantize_C(int temp[][DCT_FACTOR]) {
    int i, j;
    for(i = 0; i < DCT_FACTOR; i++) {
        for(j = 0; j < DCT_FACTOR; j++) {
            temp[i][j] = temp[i][j] * Q_C[i][j];
        }
    }
}

void copy_sub_matrix(int i, int j, int **arr, int temp[][DCT_FACTOR]) {
    int start_row, start_col, p, q;
    
    start_row = i * DCT_FACTOR;
    start_col = j * DCT_FACTOR;
    for(p = 0; p < DCT_FACTOR; p++) {
        for(q = 0; q < DCT_FACTOR; q++) {
            arr[start_row + p][start_col + q] = temp[p][q];
        }
    }
}

void exract_sub_matrix(int i, int j, int **arr, int temp[][DCT_FACTOR]) {
    int start_col, start_row, p, q;

    start_row = i * DCT_FACTOR;
    start_col = j * DCT_FACTOR;
    for(p = 0; p < DCT_FACTOR; p++) {
        for(q = 0; q < DCT_FACTOR; q++) {
            temp[p][q] = arr[start_row + p][start_col + q];
        }
    }
}
