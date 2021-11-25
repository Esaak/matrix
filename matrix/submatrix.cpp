#include <iostream>
using namespace std;
class Submatrix {
private:
    unsigned int weight=0;
    unsigned int height=0;
    double** matrix;
    void cleaner(double ** matrix2clean,unsigned int matrix2clean_height){
    for(unsigned int i = 0; i<height; i++){
        delete[] matrix2clean[i];
    }
    delete[] matrix2clean;
}

public:
    Submatrix(double** mass, unsigned int height,unsigned int weight):matrix(mass), height(height), weight(weight){
        matrix = new double* [height];
        for(unsigned int i=0; i<height; i++){
            matrix[i]= new double[weight];
            for(unsigned int j=0; j<weight; j++){
                matrix[i][j]=mass[i][j];
            }
        }
    }
    ~Submatrix(){
        for(unsigned int i = 0; i<height; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    bool input(double** mass, unsigned int user_size_height, unsigned int user_size_weight){
        if(user_size_weight!= weight && user_size_height!= height){
            cout<<"Size error\n";
            return false;
        }
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<weight; j++){
                matrix[i][j] = mass[i][j];
            }
        }
        return true;
    }
    bool multiplication(double p){
        if(p==1){
            return true;
        }
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<weight; j++){
                matrix[i][j]*=p;
            }
        }
        return true;
    }
    bool multiplication(double** m_mass,unsigned int user_size_height, unsigned int user_size_weight ){
        if(weight != user_size_height){
            return false;
        }
        double** new_matrix = new double* [height]{};
        for(unsigned int i=0; i<height; i++) {
            new_matrix[i] = new double[user_size_weight]{};
        }
        for(unsigned int i=0; i<height; i++){
            for(unsigned int j=0; j<user_size_weight; j++){
                for(unsigned int k=0; k<weight; k++){
                    new_matrix[i][j] += matrix[i][k]*m_mass[k][j];
                }
            }
        }
        return true;
    }
    bool addition(double p){
        if(p==0){
            return true;
        }
        for(int i=0; i<height; i++){
            for(int j=0; j<weight; j++){
                matrix[i][j]+=p;
            }
        }
        return true;
    }
    bool substraction(double p){
        addition(-p);
        return true;
    }
    bool division(double p){
        if(p==0){
            return false;
        }
        multiplication(1/p);
        return true;
    }


};
