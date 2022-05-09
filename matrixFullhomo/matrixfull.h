//
// Created by xiumaker on 22-5-8.
//

#ifndef COMPMATRIX_MATRIXFULL_H
#define COMPMATRIX_MATRIXFULL_H
#include "../bgv/bgv.h"
#include<iostream>
#include<NTL/ZZ.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
#include <ctime>
#include "../paillier/paillier.h"
#include "../rsa/rsa.h"

class Matrixfull {
public:
    Matrixfull(int n, int l);
    void matrixGenHrt();
    void matrixGenD();
    void matrixMulhrt();  // Hrt = H * rt
    void matrixMulhrtD(); // V = Hrt * D
    void matrixGenY();    // U^d
    void matrixDecY();    // decrypt Y


private:
    Bgv bgv;
    Mat<Ciphertext> H, rt, Hrt, D, V;
    Mat<Plaintext>  Dprime;
    Vec<Ciphertext> Y;
    Vec<Plaintext> C;
    Mat<Ciphertext> matrixEncrypt(long rows, long cols);
};


#endif //COMPMATRIX_MATRIXFULL_H
