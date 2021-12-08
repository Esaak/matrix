#include<iostream>
using namespace std;
unsigned int Gauss(double **matrix, unsigned int weight, unsigned int  height) {
    double **new_matrix = new double *[height];
    for (unsigned int i = 0; i < height; i++) {
        new_matrix[i] = new double[weight];
        for (unsigned int j = 0; j < weight; j++) {
            new_matrix[i][j] = matrix[i][j];
        }
    }
    unsigned int i;//weight
    unsigned int j;//height
    unsigned int p = 0;//счетчик куда перемещать строку
    for (i = 0; i < weight; i++) {
        for (j = 0; j < height; j++) {
            if(i==weight-1 && j == height - 1){
                new_matrix [i][j]/=new_matrix [i][j];
            }
            if (new_matrix[j][i] != 0) {
                double tmp_rows[weight];
                for (unsigned int t = i; t < weight; t++) {
                    tmp_rows[t] = new_matrix[j][t];
                    new_matrix[j][t] = new_matrix[p][t];
                    new_matrix[p][t] = tmp_rows[t];
                }//переставил строки местами
                for (unsigned int q = i; q < weight; q++) {
                    if (new_matrix[p][q] == 0) {
                        continue;
                    }
                    new_matrix[p][q] /= tmp_rows[i];//делим p строку на аpi;
                }
                double new_p1i = new_matrix[p + 1][i];
                for (unsigned int qw = p+1; qw < height; qw++) {
                    for (unsigned int q = i; q < weight; q++) {
                        new_matrix[qw][q] -= new_matrix[p][q] * new_p1i;
                    }
                }
                p++;
            }
        }
    }
    matrix=new_matrix;
    return p ;
}


int main(){

    return 0;
}