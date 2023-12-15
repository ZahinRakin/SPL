#include <time.h>
#include "header.h"

#define SIZE 1024

int main()
{
  int choice;

  printf("\033[1;31m\n\nWELCOME TO MASTER PASSWORD\n\n\n\n\033[0m");

  srand(time(0));

again:
  printf("\033[1;37m1) CREATE AN ACCOUNT.\n\n2) LOG IN.\n\n3) EXIT.\n\n4) DOWNLOAD ACCOUNT.\n\n5) DECRYPT RSA ENCRYPTED FILE.\n\nCHOICE : \033[0m");
  scanf("%d", &choice);
  printf("\n\n");
  getchar();

  if (choice == 1)
  {
    createAccount();
  }
  else if (choice == 2)
  {
    logIn();
  }
  else if (choice == 3)
  {
    exit(0);
  }
  else if (choice == 4)
  {
    download();
    main();
  }
  else if (choice == 5)
  {
    decryptRsaEncryptedFile();
    main();
  }
  else
  {
    printf("\033[1;31mWRONG COMMAND!\033[0m\n\n");
    goto again;
  }

  return 0;
}
