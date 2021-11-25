#include <iostream>
#include "submatrix.cpp"

int main() {
    double  mass [2][3] = {{1,2,3}, {4,5,6}};
    Submatrix s(&mass, 2, 3);
    for(int i=0; i<2; i++){
        for(int j=0; j<3; j++){
            cout<<mass[i][j]<<" ";
        }
        cout<<endl;
    }
}
