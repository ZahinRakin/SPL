#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRIMES 250

int prime[MAX_PRIMES];
int prime_count = 0;

int public_key;
int private_key;
int n;

int gcd(int n1, int n2) {
    int gcd;
    for(int i=1; i <= n1 && i <= n2; ++i){
        if(n1%i==0 && n2%i==0)
            gcd = i;
    }
    return gcd;
}

void primefiller() {
    bool seive[MAX_PRIMES];
    memset(seive, true, sizeof(seive));
    seive[0] = false;
    seive[1] = false;

    for (int i = 2; i < MAX_PRIMES; i++) {
        if (seive[i]) {
            prime[prime_count++] = i;
            for (int j = i * i; j < MAX_PRIMES; j += i) {
                seive[j] = false;
            }
        }
    }
}

int pickrandomprime() {
    int k = rand() % prime_count;
    int ret = prime[k];
    for (int i = k; i < prime_count - 1; i++) {
        prime[i] = prime[i + 1];
    }
    prime_count--;
    return ret;
}

void setkeys() {
    int prime1 = pickrandomprime();
    int prime2 = pickrandomprime();
    n = prime1 * prime2;
    int fi = (prime1 - 1) * (prime2 - 1);
    int e = 2;
    while (e<fi) {
        if (gcd(e, fi) == 1)
            break;
        e++;
    }
    public_key = e;
    int d = 2;
    while (1) {
        if ((d * e) % fi == 1)
            break;
        d++;
    }
    private_key = d;
}

long long int encrypt(double ascVal) {
    int e = public_key;
    long long int encrypted_text = 1;
    while (e--) {
        encrypted_text *= ascVal;
        encrypted_text %= n;
    }
    return encrypted_text;
}

long long int decrypt(int encrypted_text) {
    int d = private_key;
    long long int decrypted = 1;
    while (d--) {
        decrypted *= encrypted_text;
        decrypted %= n;
    }
    return decrypted;
}

void encoder(char *message, int *encoded) {
    for (int i = 0; message[i] != '\0'; i++) {
        encoded[i] = encrypt((int)message[i]);
    }
}

void decoder(int *encoded, char *decoded) {
    int i;
    for (i = 0; encoded[i] != '\0'; i++) {
        decoded[i] = (char)decrypt(encoded[i]);
    }
    decoded[i-3] = '\0'; // This line terminates the string properly
}


int main() {
    primefiller();
    setkeys();
    char message[] = "Test Message .zahin abdullah rakin";
    int coded[strlen(message)];

    encoder(message, coded);

    printf("Initial message:\n%s\n\n", message);
    printf("The encoded message(encrypted by public key):\n");
    for (int i = 0; i < strlen(message); i++)
        printf("%d", coded[i]);
    printf("\n\nThe decoded message(decrypted by private key):\n");
    
    char decoded[strlen(message)];
    decoder(coded, decoded);
    printf("%s\n", decoded);

    return 0;
}
