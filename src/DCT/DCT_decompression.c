#include "DCT_decompression.h"
#include "../FILE_IO/File_IO.h"
#include "../huffman/huffman_decompression.h"

void decompress_by_DCT(char *file_name) {
    int fdd, fd, fd_dummy, padded_width, padded_height, width, height;
    char decomp_file[MAX],str[MAX], ch;
    unsigned char info[54];
    check_file_extention(file_name);
    tokenize_file_name(decomp_file, file_name);

    strcpy(str, DUMMY);
    strcat(str, EXT);
    open_file_write(&fd_dummy, str);

    open_file_read(&fd, file_name); 
    open_file_write(&fdd, decomp_file);
    read(fd, info, sizeof(unsigned char) * 54);    
    write(fdd, info, sizeof(unsigned char) * 54);

    while(read(fd, &ch, 1) != 0) {
        write(fd_dummy, &ch, 1);
    }
    decompress_by_huffman(str);

    width = *(int*)&info[18];
    height = *(int*)&info[22];

    printf("original height = %d width = %d\n", height, width);

    padded_width = width;
    padded_height = height;
    if(width % DCT_FACTOR != 0) {
        padded_width +=  (DCT_FACTOR - width % DCT_FACTOR);
    }
    if(height % DCT_FACTOR != 0) {
        padded_height += (DCT_FACTOR - height % DCT_FACTOR);
    }
    close(fd_dummy);

    Apply_inverse_DCT(fdd, padded_height, padded_width);
}

void Apply_inverse_DCT(int fdd,int row, int col) {

    int **Y, **Cb, **Cr, **Y_Pixel, **Cb_Pixel, **Cr_Pixel, size, i, j, k, fd_dummy;
    char str[MAX], data[3];
    Y = get_matrix_int(row, col); 
    Cb = get_matrix_int(row, col);
    Cr = get_matrix_int(row, col);

    Y_Pixel = get_matrix_int(row, col); 
    Cb_Pixel = get_matrix_int(row, col);
    Cr_Pixel = get_matrix_int(row, col);

    strcpy(str, "/home/kishan/dsa_project_111803172/results/dummy.txt");
    open_file_read(&fd_dummy, str);

    i = j = 0;
    size = 3 * row * col; 
    for(k = 0; k < size; k = k + 3) {
        read(fd_dummy, data, 3); 
        Y[i][j] = (int)data[0] ;
        Cb[i][j] = (int)data[1];
        Cr[i][j] = (int)data[2];
        j++;
        if(j == col) {
            i = i + 1;
            j = 0;
        }
    }
    Follow_reverse_steps(fdd, row, col, Y, Cb, Cr, Y_Pixel, Cb_Pixel, Cr_Pixel);    
}

void Follow_reverse_steps(int fdd, int row, int col, int **Y, int **Cb, int **Cr, int **Y_ans, int **Cb_ans, int **Cr_ans) {
    int num_rows, num_cols, i, j, k;
    int temp[DCT_FACTOR][DCT_FACTOR], trans_temp[DCT_FACTOR][DCT_FACTOR];
    int **R, **G, **B;
    unsigned char data[3];
    R = get_matrix_int(row, col);
    G = get_matrix_int(row, col);
    B = get_matrix_int(row, col);

    num_rows = row / DCT_FACTOR;
    num_cols = col / DCT_FACTOR;

    for(i = 0; i < num_rows; i++) {
        for(j = 0; j < num_cols; j++) {
            exract_sub_matrix(i, j, Y, temp); 
            DeQuantize_Y(temp);         
            Inverse_Cosine_tranform(temp, trans_temp);
            copy_sub_matrix(i, j, Y_ans, trans_temp);
            /*
            for(int p = 0; p < DCT_FACTOR; p++) {
                for(int q = 0; q < DCT_FACTOR; q++) {
                    printf("%d ", trans_temp[p][q]);
                }
                printf("\n");
            }
            printf("\n");
            */
            exract_sub_matrix(i, j, Cb, temp); 
            DeQuantize_C(temp);         
            Inverse_Cosine_tranform(temp, trans_temp);
            copy_sub_matrix(i, j, Cb_ans, trans_temp);

            exract_sub_matrix(i, j, Cr, temp); 
            DeQuantize_C(temp);         
            Inverse_Cosine_tranform(temp, trans_temp);
            copy_sub_matrix(i, j, Cr_ans, trans_temp);
        }
    }
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            Cr_ans[i][j] = Cr_ans[i][j] - 128 ;
            Cb_ans[i][j] = Cb_ans[i][j] - 128 ;
            R[i][j] = abs(Y_ans[i][j] + 0.01 * Cb_ans[i][j]  + 1.401 * Cr_ans[i][j]);
            G[i][j] = abs(Y_ans[i][j] + (-0.336)  * Cb_ans[i][j]  + (-0.707) * Cr_ans[i][j]) ;
            B[i][j] = abs(Y_ans[i][j] +  1.783 * Cb_ans[i][j] + 0.008 * Cr_ans[i][j]) ;
        }
    }
    /* 
    for(i = 0; i < num_rows; i++) {
        for(j = 0; j < num_cols; j++) {
            exract_sub_matrix(i, j, R, temp);
            for(int p = 0; p < DCT_FACTOR; p++) {
                for(int q = 0; q < DCT_FACTOR; q++) {
                    printf("%d ", temp[p][q]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    */
    i = j = 0;
    for(k = 0; k < 3 * row * col; k = k + 3) {
        data[2] = R[i][j];
        data[1] = G[i][j];
        data[0] = B[i][j];
        j++;
        if(j == col) {
            j = 0;
            i = i + 1;
        }
        write(fdd, data, 3);
    }
    close(fdd);
}


void Inverse_Cosine_tranform(int arr[][DCT_FACTOR], int temp[][DCT_FACTOR]) {
    int i, j, u, v;
    double s;

    for (i = 0; i < DCT_FACTOR; i++) {
        for (j = 0; j < DCT_FACTOR; j++) {
            s = 0;
            for (u = 0; u < DCT_FACTOR; u++) {
                for (v = 0; v < DCT_FACTOR; v++) {
                    s += arr[u][v] * cos((2 * i + 1) * u * pi / 16) *
                        cos((2 * j + 1) * v * pi / 16) *
                        ((u == 0) ? 1 / sqrt(2) : 1.) *
                        ((v == 0) ? 1 / sqrt(2) : 1.);
                }
            }
            temp[i][j] = (int)round(s / 4) + 128;
        }
    }
}
