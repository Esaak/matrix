#include <iostream>
#include "submatrix.cpp"
using namespace std;
int main() {
    Submatrix a(3,3);
    double massa[9] = {1,1,1,-2,1,-1,2,4,-3};
    a.input(a,massa);
    Submatrix s = a.inverse(a);
    a.Gauss(a);
    s.show_matrix(s);
    a.show_matrix(a);
    return 0;
}
