//
// Created by xiumaker on 22-5-7.
//

#include "paillier.h"

NTL::ZZ generateCoprimeNumber(const NTL::ZZ& n) {
    NTL::ZZ ret;
    while (true) {
        ret = RandomBnd(n);
        if (NTL::GCD(ret, n) == 1) { return ret; }
    }
}

Paillier::Paillier() {
    /* Length in bits. */
    long keyLength = 512;
    NTL::ZZ p, q;
    GenPrimePair(p, q);
    modulus = p * q;
    generator = modulus + 1;
    NTL::ZZ phi = (p - 1) * (q - 1);
    // LCM(p, q) = p * q / GCD(p, q);
    lambda = phi / NTL::GCD(p - 1, q - 1);
    lambdaInverse = NTL::InvMod(lambda, modulus);
}

Paillier::Paillier(const NTL::ZZ& modulus, const NTL::ZZ& lambda) {
    this->modulus = modulus;
    generator = this->modulus + 1;
    this->lambda = lambda;
    lambdaInverse = NTL::InvMod(this->lambda, this->modulus);
}

void Paillier::GenPrimePair(NTL::ZZ &p, NTL::ZZ &q) {
    while (true){
        long err = 80;
        p = NTL::GenPrime_ZZ(64 / 2, err);
        q = NTL::GenPrime_ZZ(64 / 2, err);
        while (p == q) {
            q = NTL::GenPrime_ZZ(64 / 2, err);
        }
        NTL::ZZ n = p * q;
        NTL::ZZ phi = (p - 1) * (q - 1);
        if (NTL::GCD(n, phi) == 1){
            return;
        }
    }

}

NTL::ZZ Paillier::encrypt(const NTL::ZZ& message) {
    NTL::ZZ random = generateCoprimeNumber(modulus);
    NTL::ZZ ciphertext =
            NTL::PowerMod(generator, message, modulus * modulus) *
            NTL::PowerMod(random, modulus, modulus * modulus);
    return ciphertext % (modulus * modulus);
}

NTL::ZZ Paillier::encrypt(const NTL::ZZ& message, const NTL::ZZ& random) {
    NTL::ZZ ciphertext =
            NTL::PowerMod(generator, message, modulus * modulus) *
            NTL::PowerMod(random, modulus, modulus * modulus);
    return ciphertext % (modulus * modulus);
}


NTL::ZZ Paillier::decrypt(const NTL::ZZ& ciphertext) {
    /* NOTE: NTL::PowerMod will fail if the first input is too large
     * (which I assume means larger than modulus).
     */
    NTL::ZZ deMasked = NTL::PowerMod(
            ciphertext, lambda, modulus * modulus);
    NTL::ZZ power = L_function(deMasked);
    return (power * lambdaInverse) % modulus;
}

NTL::ZZ Paillier::add(const NTL::ZZ &ciphertext1, const NTL::ZZ &ciphertext2) {
    return NTL::MulMod(ciphertext1, ciphertext2, modulus * modulus);
}

NTL::ZZ Paillier::scalarmult(const NTL::ZZ &ciphertext, const NTL::ZZ &a) {
    return NTL::PowerMod(ciphertext, a, modulus * modulus);
}
