#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "paillier/paillier.h"
#include "rsa/rsa.h"
#include "matrixSemihomo/matrix.h"

void testRsa();
void testMatrix();
void testPaillier();
using namespace std;
using namespace NTL;

int main() {
    // testRsa();
    // testPaillier();
    testMatrix();


    return 0;
}

void testMatrix(){
    Matrix matrix(3, 4);
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