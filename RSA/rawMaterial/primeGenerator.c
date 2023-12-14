#include <stdio.h>
#include <math.h>

#define MAX 100

    int main() {
  /* Create an array of values, where '1' indicates that a number is prime.
   * Start by assuming all numbers are prime by setting them to 1.
   */
  char primes[MAX];
  for (int i=0; i<MAX; i++) {
    primes[i] = 1;
  }

  int limit = sqrt(MAX) + 1;
  for (int i=2; i<limit; i++) {
    if (primes[i-1]) {
      for (int j=i*i; j<=MAX; j+=i) {
        primes[j-1] = 0;
      }
    }
  }

  int count = 0;
  for (int i=2; i<=MAX; i++) {
    if (primes[i-1]) {
      printf("%d\n", i);
      count++;
    }
  }
  printf("There were %d primes up to %d", count, MAX);

  return 0;
}