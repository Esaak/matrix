#include <iostream>
#include "submatrix.cpp"
using namespace std;
int main() {
    Submatrix a(3,3);
    double massa[9] = {11,26,17,1, 3, 4,7, 5,12};
    a.input(a,massa);
    Submatrix s = a.inverse(a);
    Submatrix t = a.multiplication(a,s);
    return 0;
}
