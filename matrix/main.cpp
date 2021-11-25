#include <iostream>
using namespace std;
void f(double **mass, int a, int b){
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++){
            cout<<mass[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    double  mass [2][3] = {{1,2,3}, {4,5,6}};
     f(&mass, 2, 3);
        cout<<endl;
    }
}
