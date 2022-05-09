#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <random>
#include <cstdio>
#include "paillier/paillier.h"
#include "rsa/rsa.h"
#include "bgv/bgv.h"
#include "matrixSemihomo/matrix.h"
#include "matrixFullhomo/matrixfull.h"

void testRsa();
void testMatrix();
void testPaillier();
void testBgv();
void testFullMatrix();
using namespace std;
using namespace NTL;

int main() {
    // testRsa();
    // testPaillier();
    // testMatrix();
    testFullMatrix();
    // testBgv();


    return 0;
}

void testFullMatrix(){
    Matrixfull matrix(3,4);
    matrix.matrixGenHrt();
    matrix.matrixMulhrt();
    matrix.matrixGenD();
    matrix.matrixMulhrtD();
    matrix.matrixGenY();
    matrix.matrixDecY();
}

void testMatrix(){
    Matrix matrix(20, 25);
    matrix.matrixGenHrt();
    matrix.matrixMulhrt();
    matrix.matrixGenD();
    matrix.matrixMulhrtD();
    matrix.matrixGenU();
    matrix.matrixGenY();
    matrix.matrixDecY();
}

void testRsa(){
    Rsa rsa;
    ZZ m1 = ZZ(9);
    ZZ m2 = ZZ(5);
    ZZ en1 = rsa.encrypt(m1);
    ZZ en2 = rsa.encrypt(m2);
    ZZ en3 = rsa.mult(en1, en2);
    ZZ res = rsa.decrypt(en3);
    cout << res;
}

void testPaillier(){
    Paillier paillier;

    ZZ m1 = ZZ(5);
    ZZ m2 = ZZ(4);
    ZZ m3 = ZZ(2);
    ZZ c1 = paillier.encrypt(m1);
    ZZ c2 = paillier.encrypt(m2);
    ZZ c3 = paillier.add(c1,c2);
    ZZ c4 = paillier.scalarmult(c1, m3);
    ZZ res1 = paillier.decrypt(c3);
    ZZ res2 = paillier.decrypt(c4);
    cout << "res1 = " << res1 << endl;
    cout << "res2 = " << res2 << endl;
}

void testBgv(){
    Bgv bgv;
    srand((int)time(NULL));

    uint64_t p1 = 4;
    uint64_t p2 = 2;
    Plaintext plaintext1(uint64_to_hex_string(p1));
    Plaintext plaintext2(uint64_to_hex_string(p2));

    Ciphertext ciphertext1 = bgv.encrypt(plaintext1);
    Ciphertext ciphertext2 = bgv.encrypt(plaintext2);
    Ciphertext ciphertext3 = bgv.mult(ciphertext1, ciphertext2);
    ciphertext3 = bgv.mult(ciphertext3, ciphertext1);
    Plaintext res = bgv.decrypt(ciphertext3);
    cout << res.to_string();
//    int resultvalue;
//    sscanf(res.to_string().data() , "%x", &resultvalue);
//
//    cout << ZZ(long(resultvalue));
}