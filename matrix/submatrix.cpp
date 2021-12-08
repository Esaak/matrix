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

    Submatrix(double *mass, unsigned int height, unsigned int weight) : Submatrix(height, weight) {
        /*matrix = new double* [height];
        for(unsigned int i=0; i<height; i++){
            matrix[i]= new double[weight];*/
        for (int i = 0; i < height; i++) {
            //for(unsigned int j=0; j<weight; j++){
            memcpy(matrix[i], &mass[i], weight * sizeof(double));
        }
    }

    ~Submatrix() {
        for (unsigned int i = 0; i < height; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    bool input(double *mass, unsigned int user_size_height, unsigned int user_size_weight) {
        if (user_size_weight != weight && user_size_height != height) {
            cout << "Size error\n";
            return false;
        }
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < weight; j++) {
                matrix[i][j] = *(mass + j + i * j);
            }
        }
        return true;
    }

    bool multiplication(double p) {
        if (p == 1) {
            return true;
        }
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < weight; j++) {
                matrix[i][j] *= p;
            }
        }
        return true;
    }

    bool multiplication(const double *m_mass, unsigned int user_size_height, unsigned int user_size_weight) {
        if (weight != user_size_height) {
            return false;
        }
        double **new_matrix = new double *[height]{};
        for (unsigned int i = 0; i < height; i++) {
            new_matrix[i] = new double[user_size_weight]{};
        }
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < user_size_weight; j++) {
                for (unsigned int k = 0; k < weight; k++) {
                    new_matrix[i][j] += matrix[i][k] * (*(m_mass + j + j * k));
                }
            }
        }
        cleaner(const & matrix, height);
        matrix= new_matrix;
        return true;
    }

    bool addition(double p) {
        if (p == 0) {
            return true;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < weight; j++) {
                matrix[i][j] += p;
            }
        }
        return true;
    }

    bool addition(const double *m_mass, unsigned int user_size_height, unsigned int user_size_weight) {
        if (user_size_weight != weight && user_size_height != weight) {
            return false;
        }
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<weight; j++){
                matrix[i][j]=matrix[i][j]+(*(m_mass +j+j*i));
            }
        }
        return true;
    }

    bool substraction(double p) {
        addition(-p);
        return true;
    }
    bool substraction(const double *m_mass, unsigned int user_size_height, unsigned int user_size_weight) {
        if (user_size_weight != weight && user_size_height != weight) {
            return false;
        }
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<weight; j++){
                matrix[i][j]=matrix[i][j]-(*(m_mass +j+j*i));
            }
        }
        return true;
    }
    bool division(double p) {
        if (p == 0) {
            return false;
        }
        multiplication(1 / p);
        return true;
    }
private:
    unsigned int weight = 0;
    unsigned int height = 0;
    double **matrix;

    void cleaner(const double **matrix2clean, unsigned int matrix2clean_height){
        for (unsigned int i = 0; i < height; i++) {
            delete[] matrix2clean[i];
        }
        delete[] matrix2clean;
    }

    void Gauss(double **matrix){
        Submatrix new_matrix (*matrix,height, weight);
        while (true){
            unsigned int i=0;
            unsigned int j=0;
            for(i=0; i<weight; i++){
                for(j=0; j<height; j++){
                    if(new_matrix[j][i]!=0) {
                        break;
                    }
                }
                if(new_matrix[j][i]!=0) {
                    break;
                }
            }
            double tmp_rows[weight];
            memcpy(&tmp_rows,new_matrix[j],weight*sizeof(double));//перемещение j строки на 0 место
            memcpy(new_atrix[j], new_matrix[0], weight*sizeof(double));//перемещение j строки на 0 место
            memcpy(new_matrix[0], &tmp_rows,  weight*sizeof(double));//перемещение j строки на 0 место
            for(unsigned int q=0; q<weight; q++){
                if(new_matrix[0][q]==0){
                    continue;
                }
                new_matrix[0][q] =new_matrix[0][q]/new_matrix[0][i];//делим 0 строку на а0j;
            }
            for(unsigned int q=1; q<height; q++){
                if(new_matrix[i][q] ==0){
                    continue;
                }
                for(unsigned int t=1; t<weight; t++){
                    new_matrix[0][t] *=new_matrix[i][q];
                }
            }
            }
        }
    }


};