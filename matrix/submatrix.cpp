#include <iostream>
#include <cstring>
using namespace std;
class Submatrix {
public:
    Submatrix(unsigned int height, unsigned int weight) : height(height), weight(weight) {
        matrix = new double *[height];
        for (unsigned int i = 0; i < height; i++) {
            matrix[i] = new double[weight];

        }
    }

    /*Submatrix(double *mass, unsigned int height, unsigned int weight) : Submatrix(height, weight) {
        for (int i = 0; i < height; i++) {
            for(int j=0; j<weight; j++){
                matrix[i][j]=*(mass+j+i*j);
            }
        }
    }*/

    ~Submatrix() {
        for (unsigned int i = 0; i < height; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    bool input(Submatrix& new_matrix,const double *mass ) {
        for (unsigned int i = 0; i < new_matrix.height; i++) {
            for (unsigned int j = 0; j < new_matrix.weight; j++) {
                new_matrix.matrix[i][j] = *(mass + j + i * j);
            }
        }
        return true;
    }

    bool multiplication(Submatrix& submatrix,double p) {
        if (p == 1) {
            return true;
        }
        for (unsigned int i = 0; i < submatrix.height; i++) {
            for (unsigned int j = 0; j < submatrix.weight; j++) {
                submatrix.matrix[i][j] *= p;
            }
        }
        return true;
    }

    Submatrix* multiplication(const Submatrix &matrix2, const Submatrix &matrix1) {
        if (matrix1.weight != matrix2.height) {
            return nullptr;
        }
        Submatrix *new_matrix = new Submatrix(matrix1.height, matrix2.weight);
        for (unsigned int i = 0; i < matrix1.height; i++) {
            for (unsigned int j = 0; j < matrix2.weight; j++) {
                for (unsigned int k = 0; k < matrix2.weight; k++) {
                    new_matrix->matrix[i][j] += matrix1.matrix[i][k] *matrix2.matrix[k][j] ;
                }
            }
        }
        return new_matrix;
    }
    Submatrix* addition(const Submatrix& matrix1,const Submatrix& matrix2 ) {
        if(matrix2.weight != matrix1.weight || matrix1.height!= matrix2.height){
            return nullptr;
        }
        Submatrix* new_matrix = new Submatrix(matrix2.height, matrix2.weight);
        for(unsigned int i=0; i<matrix2.height; i++){
            for(unsigned int j=0; j<matrix1.weight; j++){
                new_matrix->matrix[i][j]=matrix1.matrix[i][j]+matrix2.matrix[i][j];
            }
        }
        return new_matrix;
    }
    Submatrix* substraction(const Submatrix& matrix1,const Submatrix& matrix2 ) {
        if(matrix2.weight != matrix1.weight || matrix1.height!= matrix2.height){
            return nullptr;
        }
        Submatrix* new_matrix = new Submatrix(matrix2.height, matrix2.weight);
        for(unsigned int i=0; i<matrix1.height; i++){
            for(unsigned int j=0; j<matrix1.weight; j++){
                new_matrix->matrix[i][j]=matrix1.matrix[i][j]-matrix2.matrix[i][j];
            }
        }
        return new_matrix;
    }

    void Gauss( Submatrix& submatrix) {
        double **new_matrix = new double *[submatrix.height];
        for (unsigned int i = 0; i < submatrix.height; i++) {
            new_matrix[i] = new double[submatrix.weight];
            for (unsigned int j = 0; j < submatrix.weight; j++) {
                new_matrix[i][j] = submatrix.matrix[i][j];
            }
        }
        unsigned int i;//weight
        unsigned int j;//height
        unsigned int p = 0;//счетчик куда перемещать строку
        for (i = 0; i < submatrix.weight; i++) {
            for (j = 0; j < submatrix.height; j++) {
                if(i==submatrix.weight-1 && j == submatrix.height - 1){
                    return;
                }
                if (new_matrix[j][i] != 0) {
                    double tmp_rows[weight];
                    for (unsigned int t = i; t < submatrix.weight; t++) {
                        tmp_rows[t] = new_matrix[j][t];
                        new_matrix[j][t] = new_matrix[p][t];
                        new_matrix[p][t] = tmp_rows[t];
                    }//переставил строки местами
                    for (unsigned int qw = p+1; qw < height; qw++) {
                        double new_p1i = new_matrix[qw][i];
                        for (unsigned int q = i; q < weight; q++) {
                            new_matrix[qw][q] -= new_matrix[p][q] *(new_p1i/new_matrix[p][i]);
                        }
                    }
                    p++;
                    submatrix.rank = p;
                }
            }
        }
        if(submatrix.weight == submatrix.height){
            submatrix.descr =1;
            for(unsigned int d=0; d<submatrix.weight; d++){
                submatrix.descr *=new_matrix[d][d];
            }
        }
    }


private:
    unsigned int weight = 0;
    unsigned int height = 0;
    double **matrix;
    unsigned int rank;
    double descr=1;

    void cleaner(Submatrix  &submatrix){
        for (unsigned int i = 0; i < submatrix.height; i++) {
            delete[] submatrix.matrix[i];
        }
        delete[] submatrix.matrix;
    }

};