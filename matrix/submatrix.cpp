#include <iostream>
using namespace std;
class Submatrix {
public:
    Submatrix(unsigned int height, unsigned int weight) : height(height), weight(weight) {
        if(weight ==0 || height==0){
            return;
        }
        matrix = new double *[height];
        for (unsigned int i = 0; i < height; i++) {
            matrix[i] = new double[weight];

        }
    }
    Submatrix(const Submatrix& submatrix): Submatrix(submatrix.height, submatrix.weight){
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < weight; j++) {
                matrix[i][j] =submatrix.matrix[i][j];
            }
        }
    }
    Submatrix& operator= (const Submatrix& submatrix) {
        if (this == &submatrix) {
            return *this;
        } else {
            if (matrix != nullptr) {
                for (unsigned int i = 0; i < height; i++) {
                    delete[] matrix[i];
                }
                delete[] matrix;
            }
            height = submatrix.height;
            weight = submatrix.weight;
            matrix = new double *[height];
            for (unsigned int i = 0; i < height; i++) {
                matrix[i] = new double[weight];
                for (unsigned int j = 0; j < weight; j++) {
                    matrix[i][j] = submatrix.matrix[i][j];
                }
            }
            det = submatrix.det;
            rank = submatrix.rank;
            return *this;
            }
        }
    ~Submatrix() {
        for (unsigned int i = 0; i < height; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void input(Submatrix& new_matrix,const double *mass ) {
        for (unsigned int i = 0; i < new_matrix.height; i++) {
            for (unsigned int j = 0; j < new_matrix.weight; j++) {
                new_matrix.matrix[i][j] = *(mass + j + i * new_matrix.weight);
            }
        }
    }

    Submatrix multiplication(Submatrix& submatrix,double p) {
        if (p == 1) {
            return submatrix;
        }
        for (unsigned int i = 0; i < submatrix.height; i++) {
            for (unsigned int j = 0; j < submatrix.weight; j++) {
                submatrix.matrix[i][j] *= p;
            }
        }
        return submatrix;
    }

    Submatrix multiplication(const Submatrix &matrix1, const Submatrix &matrix2) {
        if (matrix1.weight != matrix2.height) {
            return matrix1;
        }
        Submatrix *new_matrix = new Submatrix(matrix1.height, matrix2.weight);
        for (unsigned int i = 0; i < matrix1.height; i++) {
            for (unsigned int j = 0; j < matrix2.weight; j++) {
                for (unsigned int k = 0; k < matrix1.weight; k++) {
                    new_matrix->matrix[i][j] += matrix1.matrix[i][k] *matrix2.matrix[k][j] ;
                }
            }
        }
        return *new_matrix;
    }
    Submatrix addition(const Submatrix& matrix1,const Submatrix& matrix2 ) {
        if(matrix2.weight != matrix1.weight || matrix1.height!= matrix2.height){
            return matrix1;
        }
        Submatrix* new_matrix = new Submatrix(matrix2.height, matrix2.weight);
        for(unsigned int i=0; i<matrix2.height; i++){
            for(unsigned int j=0; j<matrix1.weight; j++){
                new_matrix->matrix[i][j]=matrix1.matrix[i][j]+matrix2.matrix[i][j];
            }
        }
        return *new_matrix;
    }
    Submatrix substraction(const Submatrix& matrix1,const Submatrix& matrix2 ) {
        if(matrix2.weight != matrix1.weight || matrix1.height!= matrix2.height){
            return matrix1;
        }
        Submatrix* new_matrix = new Submatrix(matrix2.height, matrix2.weight);
        for(unsigned int i=0; i<matrix1.height; i++){
            for(unsigned int j=0; j<matrix1.weight; j++){
                new_matrix->matrix[i][j]=matrix1.matrix[i][j]-matrix2.matrix[i][j];
            }
        }
        return *new_matrix;
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
            if(i==submatrix.weight-1 && j == submatrix.height - 1){
                break;
            }
            for (j = p; j < submatrix.height; j++) {
                if(i==submatrix.weight-1 && j == submatrix.height - 1){
                    break;
                }
                if (new_matrix[j][i] != 0) {
                    //cout<<j<<" "<<i<<endl;
                    double tmp_rows[submatrix.weight];
                    for (unsigned int t = i; t < submatrix.weight; t++) {
                        tmp_rows[t] = new_matrix[j][t];
                        new_matrix[j][t] = new_matrix[p][t];
                        new_matrix[p][t] = tmp_rows[t];
                    }//переставил строки местами
                    for (unsigned int qw = p+1; qw < submatrix.height; qw++) {
                        double new_p1i = new_matrix[qw][i];
                        for (unsigned int q = i; q < submatrix.weight; q++) {
                            new_matrix[qw][q] -= new_matrix[p][q] *(new_p1i/new_matrix[p][i]);
                        }
                    }
                    p++;
                    submatrix.rank = p;
                }
            }
        }
        if(submatrix.weight == submatrix.height){
            submatrix.det =1;
            for(unsigned int d=0; d<submatrix.weight; d++){
                submatrix.det *=new_matrix[d][d];
            }
        }
        delete[] new_matrix;
    }
    Submatrix transponse(Submatrix &submatrix){
        if(submatrix.height ==0 ||submatrix.weight ==0){
            return submatrix;
        }
        Submatrix* new_submatrix = new Submatrix(submatrix.weight, submatrix.height);
        if(submatrix.weight == submatrix.height){
            for(unsigned int i=0; i<submatrix.height; i++){
                for(unsigned int j=1+i; j<submatrix.height; j++){
                    double tmp = submatrix.matrix[i][j];
                    new_submatrix->matrix[i][j] = submatrix.matrix[j][i];
                    new_submatrix->matrix[j][i] = tmp;
                }
            }
            for(unsigned int i=0; i<submatrix.weight; i++){
                new_submatrix->matrix[i][i]=submatrix.matrix[i][i];
            }
        return *new_submatrix;
        }
        for(unsigned int t=0; t<submatrix.weight; t++){
            for(unsigned int q=0;q<submatrix.height; q++){
                new_submatrix->matrix[t][q] = submatrix.matrix[q][t];
            }
        }
        return *new_submatrix;
    }
    Submatrix  inverse(Submatrix &submatrix){
        if((submatrix.height != submatrix.weight) || submatrix.height ==0){
            return submatrix;
        }
        Gauss(submatrix);
        if(submatrix.det ==0){
            return submatrix;
        }

        else{
            Submatrix* inmatrix =new Submatrix(submatrix.height, submatrix.height);
            Submatrix tmp_matrix(inmatrix->height-1, inmatrix->weight-1);
            Submatrix tmp_matrix1(inmatrix->height, inmatrix->weight);
            tmp_matrix1 = transponse(submatrix);
            for(unsigned int i=0; i<inmatrix->height; i++){
                for(unsigned int j=0; j<inmatrix->weight; j++){
                    unsigned int i_tmp=0;
                    for(unsigned int i1=0; i1<inmatrix->height-1;i1++){
                        unsigned int j_tmp=0;
                        for(unsigned int j1=0; j1<inmatrix->weight-1; j1++){
                            if(i_tmp==i || j_tmp==j){
                                if(i_tmp==i  && i_tmp ==i1){
                                    i_tmp++;
                                }
                                if(j_tmp == j && j_tmp ==j1){
                                    j_tmp++;
                                }
                            }
                            tmp_matrix.matrix[i1][j1] = tmp_matrix1.matrix[i_tmp][j_tmp];
                            j_tmp++;
                        }
                        i_tmp++;
                    }
                    Gauss(tmp_matrix);
                    if((i+j)%2==0){
                        inmatrix->matrix[i][j]=tmp_matrix.det;
                        inmatrix->matrix[i][j]=inmatrix->matrix[i][j]/submatrix.det;
                    }
                    else{
                        inmatrix->matrix[i][j]=-tmp_matrix.det;
                        inmatrix->matrix[i][j]=inmatrix->matrix[i][j]/submatrix.det;
                    }
                }
            }
            return *inmatrix;
        }
        return submatrix;
    }
    void show_matrix(const Submatrix& submatrix){
        cout<<fixed;
        cout.precision(3);
        cout<<" Your matrix : \n";
        for(unsigned int i=0; i<submatrix.height; i++){
            for(unsigned int j=0; j<submatrix.weight; j++){
                cout<<submatrix.matrix[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"Matrix determinant = "<< submatrix.det<<endl;
        cout<<"Matrix rank = "<< submatrix.rank<<endl;
        cout<< "Matrix height = "<< submatrix.height<<endl;
        cout<<"Matrix weight = "<< submatrix.weight<<endl;

    }

private:
    double **matrix= nullptr;
    unsigned int weight = 0;
    unsigned int height = 0;
    unsigned int rank=0;
    double det=0;
    void cleaner(){
        for (unsigned int i = 0; i < height; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix= nullptr;
    }
};