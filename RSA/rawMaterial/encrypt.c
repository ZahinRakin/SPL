
#include <stdio.h>
#include <stdlib.h>

    int encrypt(int message, int public_key, int n)
    {
        int e = public_key;
        int encrypted_text = 1;
        while (e > 0) {
            encrypted_text *= message;
            encrypted_text %= n;
            e -= 1;
        }
        return encrypted_text;
    }
 
    int decrypt(int encrypted_text, int private_key, int n){
        int d = private_key;
        int decrypted = 1;
        while (d > 0) {
            decrypted *= encrypted_text;
            decrypted %= n;
            d -= 1;
        }
        return decrypted;
    }
