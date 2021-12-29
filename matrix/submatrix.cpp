#include <iostream>
using namespace std;
class Submatrix {
public:
    Submatrix(unsigned int height, unsigned int weight) : height(height), weight(weight) {
        if(weight ==0 || height==0){
            return;
        } //написать assert
        matrix = new double [height*weight];
    }
    Submatrix(const Submatrix& submatrix): Submatrix(submatrix.height, submatrix.weight){
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < weight; j++) {
                matrix[j+i*weight] =submatrix.matrix[j+i*weight];
            }
        }
    }
    Submatrix& operator= (const Submatrix& submatrix) {
        if (this == &submatrix) {
            return *this;
        } else {
            delete[] matrix;
            matrix = nullptr;
            height = submatrix.height;
            weight = submatrix.weight;
            matrix = new double [height*weight];
            for (unsigned int i = 0; i < height; i++) {
                for (unsigned int j = 0; j < weight; j++) {
                    matrix[j+i*weight] = submatrix.matrix[j+i*weight];
                }
            }
            det = submatrix.det;
            rank = submatrix.rank;
            return *this;
            }
        }
    ~Submatrix() {
        delete[] matrix;
    }
    void input(const double *mass ) {
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < weight; j++) {
                matrix[j+i*weight] = mass[j + i * weight];//подумать
            }
        }
    }
    Submatrix& operator* (double p) {
        if (p == 1) {
            return *this;
        }
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < weight; j++) {
                matrix[j+i*weight] *= p;
            }
        }
        return *this;
    }

    Submatrix& operator* (const Submatrix &submatrix) {
        if (weight != submatrix.height) {
            return *this;
        }
        Submatrix *new_matrix = new Submatrix(height, submatrix.weight);
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < submatrix.weight; j++) {
                for (unsigned int k = 0; k < weight; k++) {
                    new_matrix->matrix[j+i*weight] += matrix[k+i*weight] *submatrix.matrix[j+k*weight];
                }
            }
        }
        new_matrix->det = det*submatrix.det;
        return *new_matrix;
    }
    Submatrix& operator+ (const Submatrix& matrix2 ) {
        if(matrix2.weight != weight || height!= matrix2.height){
            return *this;
        }
        Submatrix* new_matrix = new Submatrix(matrix2.height, matrix2.weight);
        for(unsigned int i=0; i<matrix2.height; i++){
            for(unsigned int j=0; j<weight; j++){
                new_matrix->matrix[j+i*weight]=matrix[j+i*weight]+matrix2.matrix[j+i*weight];
            }
        }
        return *new_matrix;
    }
    Submatrix& operator- (double p ) {
        if(p==0){
            return *this;
        }
        Submatrix* new_matrix = new Submatrix(height, weight);
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<weight; j++){
                new_matrix->matrix[j+i*weight]=matrix[j+i*weight]-p;
            }

        }
        return *new_matrix;
    }
    Submatrix& operator- (const Submatrix& matrix2 ) {
        if(matrix2.weight != weight || height!= matrix2.height){
            return *this;
        }
        Submatrix* new_matrix = new Submatrix(matrix2.height, matrix2.weight);
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<weight; j++){
                new_matrix->matrix[j+i*weight]=matrix[j+i*weight]-matrix2.matrix[j+i*weight];
            }

        }
        return *new_matrix;
    }
    void Gauss( Submatrix& submatrix) {
        double *new_matrix = new double [submatrix.height* submatrix.weight];
        for (unsigned int i = 0; i < submatrix.height; i++) {
            for (unsigned int j = 0; j < submatrix.weight; j++) {
                new_matrix[j+i*weight] = submatrix.matrix[j+i*weight];
            }
        }
        unsigned int i;//weight
        unsigned int j;//height
        unsigned int p = 0;//счетчик куда перемещать строку
        int sign=0;
        for (i = 0; i < submatrix.weight; i++) {
            if(i==submatrix.weight-1 && j == submatrix.height - 1){
                break;
            }
            for (j = p; j < submatrix.height; j++) {
                if(i==submatrix.weight-1 && j == submatrix.height - 1){
                    break;
                }
                if (new_matrix[j*height+i] != 0) {
                    //cout<<j<<" "<<i<<endl;
                    double tmp_rows[submatrix.weight];
                    if(j!=p) {
                        for (unsigned int t = i; t < submatrix.weight; t++) {
                            tmp_rows[t] = new_matrix[j*weight+t];
                            new_matrix[j*submatrix.weight + t] = new_matrix[p*submatrix.weight + t];
                            new_matrix[p*submatrix.weight + t] = tmp_rows[t];
                        }//переставил строки местами
                        sign++;
                    }
                    for (unsigned int qw = p+1; qw < submatrix.height; qw++) {
                        double new_p1i = new_matrix[qw*submatrix.weight + i];
                        for (unsigned int q = i; q < submatrix.weight; q++) {
                            new_matrix[qw*submatrix.weight + q] -= new_matrix[p*submatrix.weight + q] *(new_p1i/new_matrix[p*submatrix.weight + i]);
                        }
                    }
                    p++;
                }
            }
        }
        for(unsigned int i1 =0; i1<submatrix.height; i1++){
            for(unsigned int j1=0; j1<submatrix.weight; j1++){
                if(new_matrix[i1*submatrix.weight + j1]!=0){
                    submatrix.rank++;
                    break;
                }
            }
        }
        if(submatrix.weight == submatrix.height){
            if(sign%2==0){
                submatrix.det =1;
            }
            else{
                submatrix.det =-1;
            }
            for(unsigned int d=0; d<submatrix.weight; d++){
                submatrix.det *=new_matrix[d*submatrix.weight + d];
            }
        }
        delete[] new_matrix;
    }
    Submatrix transponse(){
        if(height ==0 ||weight ==0){
            return *this;
        }
        Submatrix* new_submatrix = new Submatrix(weight, height);
        if(weight == height){
            for(unsigned int i=0; i<height; i++){
                for(unsigned int j=1+i; j<height; j++){
                    double tmp = matrix[i*height + j];
                    new_submatrix->matrix[i*height+j] = matrix[j*height+i];
                    new_submatrix->matrix[j*height+i] = tmp;
                }
            }
            for(unsigned int i=0; i<weight; i++){
                new_submatrix->matrix[i*weight + i]=matrix[i*weight + i];
            }
            return *new_submatrix;
        }
        for(unsigned int t=0; t<weight; t++){
            for(unsigned int q=0;q<height; q++){
                new_submatrix->matrix[t*height + q] =matrix[q*weight + t];
            }
        }
        return *new_submatrix;
    }
    void Gauss() {
        double *new_matrix = new double [height*weight];
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < weight; j++) {
                new_matrix[i*weight + j] = matrix[j+i*weight];
            }
        }
        unsigned int i;//weight
        unsigned int j;//height
        unsigned int p = 0;//счетчик куда перемещать строку
        int sign=0;
        for (i = 0; i < weight; i++) {
            if(i==weight-1 && j == height - 1){
                break;
            }
            for (j = p; j < height; j++) {
                if(i==weight-1 && j == height - 1){
                    break;
                }
                if (new_matrix[j*weight + i] != 0) {
                    //cout<<j<<" "<<i<<endl;
                    double tmp_rows[weight];
                    if(j!=p) {
                        for (unsigned int t = i; t < weight; t++) {
                            tmp_rows[t] = new_matrix[j*weight + t];
                            new_matrix[j*weight + t] = new_matrix[p*weight + t];
                            new_matrix[p*weight + t] = tmp_rows[t];
                        }//переставил строки местами
                        sign++;
                    }
                    for (unsigned int qw = p+1; qw < height; qw++) {
                        double new_p1i = new_matrix[qw*weight + i];
                        for (unsigned int q = i; q < weight; q++) {
                            new_matrix[qw*weight + q] -= new_matrix[p*weight + q] *(new_p1i/new_matrix[p*weight + i]);
                        }
                    }
                    p++;
                }
            }
        }
        for(unsigned int i1 =0; i1<height; i1++){
            for(unsigned int j1=0; j1<weight; j1++){
                if(new_matrix[i1*weight + j1]!=0){
                    rank++;
                    break;
                }
            }
        }
        if(weight == height){
            if(sign%2==0){
                det =1;
            }
            else{
                det =-1;
            }
            for(unsigned int d=0; d<weight; d++){
                det *=new_matrix[d*weight+ d];
            }
        }
        delete[] new_matrix;
    }
    static Submatrix transponse(Submatrix &submatrix){
        if(submatrix.height ==0 ||submatrix.weight ==0){
            return submatrix;
        }
        Submatrix* new_submatrix = new Submatrix(submatrix.weight, submatrix.height);
        if(submatrix.weight == submatrix.height){
            for(unsigned int i=0; i<submatrix.height; i++){
                for(unsigned int j=1+i; j<submatrix.height; j++){
                    double tmp = submatrix.matrix[i*submatrix.height+j];
                    new_submatrix->matrix[i*submatrix.height+ j] = submatrix.matrix[j*submatrix.height + i];
                    new_submatrix->matrix[j*submatrix.height + i] = tmp;
                }
            }
            for(unsigned int i=0; i<submatrix.weight; i++){
                new_submatrix->matrix[i*submatrix.weight + i]=submatrix.matrix[i*submatrix.weight + i];
            }
        return *new_submatrix;
        }
        for(unsigned int t=0; t<submatrix.weight; t++){
            for(unsigned int q=0;q<submatrix.height; q++){
                new_submatrix->matrix[t*submatrix.height + q] = submatrix.matrix[q*submatrix.weight + t];
            }
        }
        return *new_submatrix;
    }
    Submatrix  inverse(){
        if((height != weight) || height ==0){
            return *this;
        }
        Gauss();
        if(det ==0){
            return *this;
        }

        else{
            Submatrix* inmatrix =new Submatrix(height, height);
            Submatrix tmp_matrix(inmatrix->height-1, inmatrix->weight-1);
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
                            tmp_matrix.matrix[i1 * inmatrix->weight-1 + j1] = matrix[i_tmp * inmatrix->weight-1 + j_tmp];
                            j_tmp++;
                        }
                        i_tmp++;
                    }
                    Gauss(tmp_matrix);
                    if((i+j+2)%2==0){
                        inmatrix->matrix[i * inmatrix->weight + j]=tmp_matrix.det;
                        inmatrix->matrix[i * inmatrix->weight + j]=inmatrix->matrix[i * inmatrix->weight + j]/det;
                    }
                    else{
                        inmatrix->matrix[i * inmatrix->weight + j]=-tmp_matrix.det;
                        inmatrix->matrix[i * inmatrix->weight + j]=inmatrix->matrix[i * inmatrix->weight + j]/det;
                    }
                }
            }
            *inmatrix =transponse(*inmatrix);
            return *inmatrix;
        }
    }
    void show_matrix(){
        cout<<fixed;
        cout.precision(3);
        cout<<" Your matrix : \n";
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<weight; j++){
                cout<<matrix[i*weight + j]<<" ";
            }
            cout<<endl;
        }
        cout<<"Matrix determinant = "<< det<<endl;
        cout<<"Matrix rank = "<< rank<<endl;
        cout<< "Matrix height = "<< height<<endl;
        cout<<"Matrix weight = "<< weight<<endl;

    }

private:
    unsigned int height = 0;
    unsigned int weight = 0;
    double *matrix= nullptr;
    unsigned int rank=0;
    double det=0;
    void cleaner(){
        delete[] matrix;
        matrix= nullptr;
    }
};