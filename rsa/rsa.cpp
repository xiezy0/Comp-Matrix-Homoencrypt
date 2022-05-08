//
// Created by xiumaker on 22-5-7.
//
#include<iostream>

#include "rsa.h"

Rsa::Rsa(){
    ZZ p = GenPrime_ZZ(64, 80);
    ZZ q = GenPrime_ZZ(64, 80);
    n = p * q;
    phi_of_n = (p-1)*(q-1);
    ZZ i = (ZZ)1;
    long bits_of_n = 0;
    for( ; i <= n; i *= 10) {
        bits_of_n++;
    }
    public_key = GenPrime_ZZ(bits_of_n/2, 80);
    private_key = InvMod(public_key, phi_of_n);
}

ZZ Rsa::encrypt(const ZZ& message) {
    return PowerMod(message, public_key, n);
}

ZZ Rsa::mult(const ZZ& encrypted_message1,const ZZ& encrypted_message2) {
    return MulMod(encrypted_message1, encrypted_message2, n);
}

ZZ Rsa::decrypt(const ZZ& encrypted_message) {
    return PowerMod(encrypted_message, private_key, n);
}

void rsatest(){
    ZZ p, q, n, phi_of_n, public_key, private_key, message1, message2;
    int no_of_bits;

    std::cout<<"Enter no of bits : ";
    std::cin>>no_of_bits;

    // generating p and q prime numbers
    p = GenPrime_ZZ(no_of_bits, 80);
    q = GenPrime_ZZ(no_of_bits, 80);
    n = p * q;
    phi_of_n = (p-1)*(q-1);

    ZZ i = (ZZ)1;
    long bits_of_n = 0;
    for( ; i <= n; i *= 10) {
        bits_of_n++;
    }

    public_key = GenPrime_ZZ(bits_of_n/2, 80);
    private_key = InvMod(public_key, phi_of_n);

    std::cout<<"\nEnter Message to decrypt : ";
    std::cin>>message1;

    std::cout<<"\nEnter Message to decrypt : ";
    std::cin>>message2;

    // Encryption of message using public key
    ZZ encrypted_message1 = PowerMod(message1, public_key, n);
    ZZ encrypted_message2 = PowerMod(message2, public_key, n);
    ZZ encrypted_message12 = MulMod(encrypted_message1, encrypted_message2, n);

    ZZ decrypted_message = PowerMod(encrypted_message12, private_key, n);

    std::cout<<"\np = "<<p<<"\n";
    std::cout<<"\nq = "<<q<<"\n";
    std::cout<<"\nn = "<<n<<"\n";
    std::cout<<"\nphi of n = "<<phi_of_n<<"\n";
    std::cout<<"\npublic key = "<<public_key<<"\n";
    std::cout<<"\nprivate key = "<<private_key<<"\n";
    std::cout<<"\nprivate key * public key (mod phi_of_n)= "<<MulMod(public_key, private_key, phi_of_n)<<"\n";
    std::cout<<"\nEncrypted Message = "<<encrypted_message12<<"\n";
    std::cout<<"\nDecrypted Message = "<<decrypted_message<<"\n";
}