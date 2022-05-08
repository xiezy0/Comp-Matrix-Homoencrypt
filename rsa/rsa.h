//
// Created by xiumaker on 22-5-7.
//
#include<NTL/ZZ.h>
using namespace NTL;

#ifndef COMPMATRIX_RSA_H
#define COMPMATRIX_RSA_H


class Rsa {
public:
    Rsa();

    ZZ encrypt(const ZZ& message);
    ZZ mult(const ZZ& encrypted_message1,const ZZ& encrypted_message2);
    ZZ decrypt(const ZZ& encrypted_message);

private:
    ZZ n, phi_of_n, public_key, private_key;
};
void rsatest();

#endif //COMPMATRIX_RSA_H
