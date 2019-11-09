#include "DCT_compression.h"
#include "Quantized.h"
#include "../FILE_IO/File_IO.h"

void compress_by_DCT(char *file_name) {
    int height, width, padded_width, padded_height;
    int **Y_Pixel, **Cb_Pixel, **Cr_Pixel;
    int **Cosine_matrix_Y, **Cosine_matrix_Cb, **Cosine_matrix_Cr;

    get_height_width(file_name, &height, &width);
    padded_width = width;
    padded_height = height;
    if(width % DCT_FACTOR != 0) {
        padded_width +=  (DCT_FACTOR - width % DCT_FACTOR);
    }
    if(height % DCT_FACTOR != 0) {
        padded_height += (DCT_FACTOR - height % DCT_FACTOR);
    }

    Y_Pixel = get_matrix_int(padded_height, padded_width);
    Cb_Pixel = get_matrix_int(padded_height, padded_width);
    Cr_Pixel = get_matrix_int(padded_height, padded_width);
    
    Cosine_matrix_Y = get_matrix_int(padded_height, padded_width);
    Cosine_matrix_Cb = get_matrix_int(padded_height, padded_width);
    Cosine_matrix_Cr = get_matrix_int(padded_height, padded_width);

    readBMP(file_name, Y_Pixel, Cb_Pixel, Cr_Pixel);
    
    Apply_DCT(padded_width,padded_height, Y_Pixel, Cb_Pixel, Cr_Pixel,Cosine_matrix_Y, Cosine_matrix_Cb, Cosine_matrix_Cr);
    
    write_in_file(padded_height, padded_width, Cosine_matrix_Y, Cosine_matrix_Cb, Cosine_matrix_Cr); 

    free(Y_Pixel);
    free(Cb_Pixel);
    free(Cr_Pixel);
    free(Cosine_matrix_Y);
    free(Cosine_matrix_Cb);
    free(Cosine_matrix_Cr);
}

void write_in_file(int row, int col, int **arrY, int **arrCb, int **arrCr) {
    int fd_dummy, i, j;
    char data[3];
    open_file_write(&fd_dummy, DUMMY);
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            data[0] = (char)arrY[i][j];
            data[1] = (char)arrCb[i][j];
            data[2] = (char)arrCr[i][j];
            write(fd_dummy, data, 3);
        }
    }
}

void Apply_DCT(int width, int height, int **Y_Pixel, int **Cb_Pixel, int **Cr_Pixel, int **Y_ans, int **Cb_ans, 
    int **Cr_ans) {
    int num_cols, num_rows, i, j;
    int temp[DCT_FACTOR][DCT_FACTOR];
    float trans_temp[DCT_FACTOR][DCT_FACTOR]; 

    num_cols = width / DCT_FACTOR;
    num_rows = height / DCT_FACTOR;
    printf("height = %d width = %d\n", height, width);
    printf("num_rows = %d num_cols = %d\n", num_rows, num_cols);

    for(i = 0; i < num_rows; i++) {
        for(j = 0;j < num_cols; j++) {
            exract_sub_matrix(i, j, Y_Pixel, temp);        
            Cosine_tranform(temp, trans_temp);
            Quantize_Y(trans_temp, temp);
            copy_sub_matrix(i, j, Y_ans, temp);
            
            exract_sub_matrix(i, j, Cb_Pixel, temp);        
            Cosine_tranform(temp, trans_temp);
            Quantize_C(trans_temp, temp);
            copy_sub_matrix(i, j, Cb_ans, temp);

            exract_sub_matrix(i, j, Cr_Pixel, temp);        
            Cosine_tranform(temp, trans_temp);
            Quantize_C(trans_temp, temp);
            copy_sub_matrix(i, j, Cb_ans, temp);
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
            temp[p][q] = 128 - arr[start_row + p][start_col + q];
        }
    }
}

void Cosine_tranform(int arr[][DCT_FACTOR], float temp[][DCT_FACTOR]) {
    int i, j, k, l; 
    float ci, cj, dct1, sum; 

    for (i = 0; i < DCT_FACTOR; i++) { 
        for (j = 0; j < DCT_FACTOR; j++) { 

            // ci and cj depends on frequency as well as 
            // number of row and columns of specified matrix 
            if (i == 0) 
                ci = 1 / sqrt(DCT_FACTOR); 
            else
                ci = sqrt(2) / sqrt(DCT_FACTOR); 
            if (j == 0) 
                cj = 1 / sqrt(DCT_FACTOR); 
            else
                cj = sqrt(2) / sqrt(DCT_FACTOR); 

            // sum will temporarily store the sum of  
            // cosine signals 
            sum = 0; 
            for (k = 0; k < DCT_FACTOR; k++) { 
                for (l = 0; l < DCT_FACTOR; l++) { 
                    dct1 = arr[k][l] *  
                        cos((2 * k + 1) * i * pi / (2 * DCT_FACTOR)) *  
                        cos((2 * l + 1) * j * pi / (2 * DCT_FACTOR)); 
                    sum = sum + dct1; 
                } 
            } 
            temp[i][j] = ci * cj * sum; 
        } 
    } 
}

void get_height_width(char *file_name, int *height, int *width) {
    unsigned char info[54]; 
    int fd;
    open_file_read(&fd, file_name);
    read(fd, info ,sizeof(unsigned char) * 54);
    (*width) = *(int*)&info[18];
    (*height) = *(int*)&info[22];
    close(fd);
}

void readBMP(char* file_name, int **Y_Pixel, int **Cb_Pixel, int **Cr_Pixel) {
    int i, j, k, fd;
    int  R, G, B;
    open_file_read(&fd, file_name);
    unsigned char info[54];
    read(fd, info ,sizeof(unsigned char) * 54); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    unsigned char data[3];

    int size = 3 * width * height;
    i = j = 0;
    for(k = 0; k < size; k += 3) {
        read(fd, data, sizeof(unsigned char) * 3);
        R = (int)data[2];
        G = (int)data[1];
        B = (int)data[0];
        Y_Pixel[i][j] = (0.3) * R +  (0.59) * G + (0.11) * B;
        Cb_Pixel[i][j] = 128 +  (-0.169) * R + (-0.331) * G + (0.5) * B;
        Cr_Pixel[i][j] = 128 +  (0.5) * R +  (-0.419) * G + (-0.081) * B;
        j++;
        if(j == width) {
            j = 0;
            i = i + 1;
        }
    } 
    close(fd);
}


