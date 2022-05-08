//
// Created by xiumaker on 22-5-7.
//

#ifndef COMPMATRIX_PAILLIER_H
#define COMPMATRIX_PAILLIER_H
#include <NTL/ZZ.h>
#include <NTL/ZZ_pXFactoring.h>

class Paillier {
public:
    /* Completely generate everything, from scratch */
    Paillier();
    Paillier(const NTL::ZZ& modulus, const NTL::ZZ& lambda);
    //Paillier(path to public key, path to private key).

    /* Paillier encryption function. Takes in a message from the
     * integers modulo n (Paillier.modulus) and returns a message in
     * the integers modulo n**2.
     *
     * Parameters
     * ==========
     * NTL::ZZ message : The message to encrypt, as a number.
     *
     * Returns
     * =======
     * NTL:ZZ ciphertext : The encyrpted message.
     */
    NTL::ZZ encrypt(const NTL::ZZ& message);
    NTL::ZZ lcm(NTL::ZZ x, NTL::ZZ y){
        NTL::ZZ ans = (x * y) / NTL::GCD(x,y);
        return ans;
    }

    /* Paillier encryption function with provided randomness, if user
     * wants to provide their own randomness.
     *
     * Random number should be coprime to modulus.
     *
     * Parameters
     * ==========
     * NTL::ZZ message : The message to encrypt, as a number.
     * NTL::ZZ random : The random mask.
     *
     * Returns
     * =======
     * NTL:ZZ ciphertext : The encyrpted message.
     */
    NTL::ZZ encrypt(const NTL::ZZ& message, const NTL::ZZ& random);
    NTL::ZZ add(const NTL::ZZ& ciphertext1, const NTL::ZZ& ciphertext2);
    NTL::ZZ scalarmult(const NTL::ZZ& ciphertext, const NTL::ZZ& a);

    /* Paillier decryption function. Takes in a cipertext from Z mod
     * n**2 and returns a message in the Z mod n.
     *
     * Parameters
     * ==========
     * NTL::ZZ cipertext : The encrypted message.
     *
     * Returns
     * =======
     * NTL::ZZ message : The original message.
     */
    NTL::ZZ decrypt(const NTL::ZZ& ciphertext);


private:
    /* modulus = pq, where p and q are primes */
    NTL::ZZ modulus;
    NTL::ZZ generator;
    NTL::ZZ lambda;
    NTL::ZZ lambdaInverse;

    /* The L function in the paillier cryptosystem.  See
     * <https://en.wikipedia.org/wiki/Paillier_cryptosystem> for more
     * details.
     *
     * Parameters
     * ==========
     * NTL::ZZ x : The argument to L.
     * NTL::ZZ n : The paillier modulus.
     *
     * Returns
     * =======
     * NTL::ZZ result : (x - 1) / n
     */
    NTL::ZZ L_function(const NTL::ZZ& n) { return (n - 1) / modulus; }

    static void GenPrimePair(NTL::ZZ &p, NTL::ZZ &q);
};


#endif //COMPMATRIX_PAILLIER_H
