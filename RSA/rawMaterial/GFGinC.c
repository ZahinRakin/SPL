#include <stdbool.h>
#include "rsaheader.h"

void primeFiller() {
    for (int i = 0; i < max; i++) {
        sieve[i] = true;
    }

    sieve[0] = false;
    sieve[1] = false;

    for (int i = 2; i < max; i++) {
        for (int j = i * 2; j < 250; j += i) {
            sieve[j] = false;
        }
    }

    for (int i = 0; i < sieve.length; i++) {
        if (sieve[i]) {
            prime.add(i);
        }
    }
}