//
// Created by xiumaker on 22-5-7.
//

#ifndef COMPMATRIX_MATRIX_H
#define COMPMATRIX_MATRIX_H
#include<iostream>
#include<NTL/ZZ.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
#include "../paillier/paillier.h"
#include "../rsa/rsa.h"

using namespace NTL;
using namespace std;

class Matrix {
public:
    Matrix(int n, int l);
    void matrixGenHrt();
    void matrixGenD();
    void matrixMulhrt();  // Hrt = H * rt
    void matrixMulhrtD(); // V = Hrt * D
    void matrixGenU();    // decrypt V and encryt Vprime
    void matrixGenY();    // U^d
    void matrixDecY();    // decrypt Y


private:
    Rsa rsa;
    Paillier paillier;
    Mat<ZZ> H, rt, Hrt, D, Dprime, V, U, Vprime;
    Vec<ZZ> Y, C;
    Mat<ZZ> matrixEncrypt(long rows, long cols);
};

#endif //COMPMATRIX_MATRIX_H
