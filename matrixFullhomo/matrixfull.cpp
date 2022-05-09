//
// Created by xiumaker on 22-5-8.
//

#include "matrixfull.h"

Matrixfull::Matrixfull(int n, int l) {
    Bgv bgv1;
    bgv = bgv1;

    H.SetDims(n,l);
    rt.SetDims(l,1);
    Hrt.SetDims(n, l);
    D.SetDims(n, l);
    Dprime.SetDims(n, l);
    V.SetDims(n,l);
    Y.SetLength(n);
    C.SetLength(n);
}

Mat<Ciphertext> Matrixfull::matrixEncrypt(long rows, long cols) {
    Mat<Ciphertext> matrix;
    srand((int)time(nullptr));
    matrix.SetDims(rows, cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            uint64_t p = rand()%1000;
            //cout << p << endl;
            Plaintext plaintext(uint64_to_hex_string(p));

            Ciphertext envalue = bgv.encrypt(plaintext);
            matrix.put(i, j, envalue);
        }
    }
    return matrix;
}

void Matrixfull::matrixGenHrt() {
    H = matrixEncrypt(H.NumRows(), H.NumCols());
    rt = matrixEncrypt(H.NumRows(),1);
    //cout << bgv.decrypt(H.get(1,1)).to_string() << endl;
//    cout << H << endl;
//    cout << rt << endl;
}

void Matrixfull::matrixGenD() {
    srand((int)time(nullptr));
    for(int i = 0; i < Dprime.NumRows(); i++){
        for(int j = 0; j < Dprime.NumCols(); j++) {
            uint64_t p = rand()%1000;
            Plaintext plaintext(uint64_to_hex_string(p));
            Dprime.put(i, j, plaintext);
            Ciphertext envalue = bgv.encrypt(plaintext);
            D.put(i, j, envalue);
        }
    }
}

void Matrixfull::matrixMulhrt() {
    for(int i = 0; i < H.NumRows(); i++) {
        for(int j = 0; j< H.NumCols(); j++) {
            Ciphertext hrt = bgv.mult(H.get(i, j), rt.get(i, 0));
            Hrt.put(i, j, hrt);
        }
    }
    //cout << bgv.decrypt(Hrt.get(1,1)).to_string()<< endl;
}

void Matrixfull::matrixMulhrtD() {
    for(int i = 0; i< Hrt.NumRows(); i++){
        for(int j = 0; j< Hrt.NumCols(); j++){
            Ciphertext v = bgv.mult(Hrt.get(i, j), D.get(i, j));
            V.put(i, j, v);
        }
    }
    //cout << bgv.decrypt(V.get(1,1)).to_string();
}

void Matrixfull::matrixGenY() {
    for(int i = 0; i < V.NumRows(); i++) {
        Plaintext zero(uint64_to_hex_string(0));
        Ciphertext vecValue = bgv.encrypt(zero);
        for (int j = 0; j < V.NumCols(); j++) {
            Ciphertext udprime = bgv.multscalar(V.get(i, j), Dprime.get(i, j));
            vecValue = bgv.add(udprime, vecValue);
            if(j == V.NumCols() - 1){
                Y.put(i, vecValue);
            }
        }
    }
}

void Matrixfull::matrixDecY() {
    for(int i = 0; i < Y.length(); i++){
        Plaintext p = bgv.decrypt(Y.get(i));
        cout << p.to_string()<< endl;
        C.put(i, p);
    }
}


