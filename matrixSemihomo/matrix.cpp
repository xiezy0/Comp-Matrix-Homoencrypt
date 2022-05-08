//
// Created by xiumaker on 22-5-7.
//

#include "matrix.h"

Matrix::Matrix(int n, int l) {
    Rsa rsa1;
    rsa = rsa1;
    Paillier paillier1;
    paillier = paillier1;

    H.SetDims(n,l);
    rt.SetDims(l,1);
    Hrt.SetDims(n, l);
    D.SetDims(n, l);
    Dprime.SetDims(n, l);
    V.SetDims(n,l);
    Vprime.SetDims(n, l);
    U.SetDims(n,l);
    Y.SetLength(n);
    C.SetLength(n);
}

Mat<ZZ> Matrix::matrixEncrypt(long rows, long cols) {
    Mat<ZZ> matrix;
    matrix.SetDims(rows, cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            ZZ value = RandomBits_ZZ(10);
            ZZ envalue = rsa.encrypt(value);
            matrix.put(i, j, envalue);
        }
    }
    return matrix;
}

void Matrix::matrixGenHrt() {
    H = matrixEncrypt(H.NumRows(), H.NumCols());
    rt = matrixEncrypt(H.NumRows(),1);
//    cout << H << endl;
//    cout << rt << endl;
}

void Matrix::matrixGenD() {
    for(int i = 0; i < Dprime.NumRows(); i++){
        for(int j = 0; j < Dprime.NumCols(); j++) {
            ZZ value = RandomBits_ZZ(10);
            Dprime.put(i, j, value);
            D.put(i, j, rsa.encrypt(value));
        }
    }
}

void Matrix::matrixMulhrt() {
    for(int i = 0; i < H.NumRows(); i++) {
        for(int j = 0; j< H.NumCols(); j++) {
            ZZ hrt = rsa.mult(H.get(i, j), rt.get(i, 0));
            Hrt.put(i, j, hrt);
        }
    }
    //cout << Hrt << endl;
}

void Matrix::matrixMulhrtD() {
    for(int i = 0; i< Hrt.NumRows(); i++){
        for(int j = 0; j< Hrt.NumCols(); j++){
            ZZ v = rsa.mult(Hrt.get(i, j), D.get(i, j));
            V.put(i, j, v);
        }
    }
    //cout << V << endl;
}

void Matrix::matrixGenU() {
    for(int i = 0; i< V.NumRows(); i++) {
        for (int j = 0; j < V.NumCols(); j++) {
            ZZ vprime = rsa.decrypt(V.get(i, j));
            Vprime.put(i, j, vprime);
            U.put(i, j, paillier.encrypt(vprime));
        }
    }
    // cout << Vprime << endl;
}

void Matrix::matrixGenY() {
    for(int i = 0; i < U.NumRows(); i++) {
        ZZ vecValue = paillier.encrypt(ZZ(0));
        for (int j = 0; j < U.NumCols(); j++) {
            ZZ udprime = paillier.scalarmult(U.get(i, j), Dprime.get(i, j));
            vecValue = paillier.add(udprime, vecValue);
            if(j == U.NumCols() - 1){
                Y.put(i, vecValue);
            }
        }
    }
    // cout << Y << endl;
}

void Matrix::matrixDecY() {
    for(int i = 0; i < Y.length(); i++){
        C.put(i, paillier.decrypt(Y.get(i)));
    }
    cout << C << endl;
}


