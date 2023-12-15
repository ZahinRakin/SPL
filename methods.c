#include "header.h"

void logIn()
{
  FILE *fp;
  char username[80];
  char password[53];
  char line[55];
  char choice;

again:
  printf("\033[1;37musername: \033[0m");
  scanf("%s", username);
  getchar();
  printf("\n\n");
  strcat(username, ".txt");

  printf("\033[1;31mpassword: \033[0m");
  scanf("%s", password);
  getchar();
  printf("\n\n");

  fp = fopen(username, "r");
  if (fp == NULL)
  {
    printf("\033[1;31mYou don't have an account!\n\n\033[0m");
    main();
  }

  fgets(line, sizeof(line), fp);
  fclose(fp);

  if (line == NULL)
  {
    printf("\033[1;31mProblem occured while reading the first line\n\n\033[0m");
    exit(0);
  }
  removeNewLine(line, strlen(line));

  if (strcmp(line, password))
  {
    printf("\x1b[31m");
    printf("Wrong password!\n");
    printf("\x1b[0m");
    goto again;
  }

  printf("\033[1;37ma) Store Information.\n\nb) View Information.\033[1;32m\n\nc) Update information\n\nd) log out.\n\ne) Upload Account\n\nchoice: ");
  scanf("%c", &choice);
  getchar();
  printf("\n\n\033[0m");
  if (choice == 'a')
  {
    storeInformation(username);
  }
  else if (choice == 'b')
  {
    viewInformation(username);
  }
  else if (choice == 'c')
  {
    updatePassword(username);
  }
  else if (choice == 'd')
  {
    main();
  }
  else if (choice == 'e')
  {
    upload(username);
  }
  else
  {
    printf("\x1b[31m");
    printf("Wrong command.\n");
    printf("\x1b[0m");
  }
}

void storeInformation(char *username)
{
  FILE *fp;
  int choice;
  char *password;
  char takePass[53];
  char pass[100] = "Password: ";
  char websiteAddress[100];
  char web[150] = "Website Address: ";
  char emailAddress[80];
  char email[100] = "Email: ";
  int accountNumber = 1;
  char line[200];
  int lineNumber = 1;
  unsigned char *output; // this is for AES encrypt.
  unsigned char key[16]; // line number 162

  fp = fopen(username, "r");
  if (fp == NULL)
  {
    printf("\033[1;31mFILE CANN'T BE OPENED!\n\n\033[0m");
    exit(1);
  }
  while (fgets(line, sizeof(line), fp))
  {
    if (((lineNumber - 2) % 5 == 0) && atoi(line) != 0)
    {
      accountNumber = atoi(line);
      accountNumber++;
    }
    lineNumber++;
  }

  fclose(fp);
  // this finds out the account number for indexing new accounts.
  printf("\033[1;37mWebsite Address: \033[0m");
  scanf("%s", websiteAddress);
  getchar();
  strcat(web, websiteAddress);
  printf("\n\n");
  // here the website address would be added to the file

  printf("\033[1;37mEmail Address: \033[0m");
  scanf("%s", emailAddress);
  getchar();
  strcat(email, emailAddress);
  printf("\n\n");
  // here the email address would be added to the file
  // storing password porcess starts form now on.

  printf("\033[1;37m1) Generate Password.\n\n2) Give password.\n\n\033[1;32mchoice: \033[0m");
  scanf("%d", &choice);
  getchar();
  printf("\n\n");

  if (choice == 1)
  {
    password = generatePassword(password);
  }
  else if (choice == 2)
  {
  again:
    printf("\033[1;31mRemember to keep password within 6-52 character:\033[0m ");
    scanf("%s", takePass);
    getchar();
    printf("\n");
    int strength = checkStrength(takePass, strlen(takePass));
    if (strength <= 0)
    {
      goto again;
    }
    else
    {
      password = takePass;
    }
  }
  else
  {
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
    exit(1);
  }
  strcat(pass, password); // i have a confusion since pass is arr and password is pointer. shouldn't create any problem though.

  printf("Enter key: "); // getting the key
  fgets(key, sizeof(key), stdin);
  removeNewLine(key, strlen(key));
  int pl = padding(key); // purified key..

  // opening the file for storing updated infos.
  fp = fopen(username, "a");
  if (fp == NULL)
  {
    printf("\033[1;31mFILE CANN'T BE OPENED!\n\n\033[0m");
    exit(1);
  }
  // storing account informations..
  fprintf(fp, "%d.\n", accountNumber);

  output = cipher(web, output, key);
  bytesToString(output, web);
  fprintf(fp, "%s\n", web); // Wesite address
  free(output);

  output = cipher(email, output, key);
  bytesToString(output, email);
  fprintf(fp, "%s\n", email); // Email Address
  free(output);

  output = cipher(pass, output, key);
  bytesToString(output, pass);
  fprintf(fp, "%s\n", pass); // Password
  free(output);

  fprintf(fp, "---------------------------------------------------------------------\n"); // locator of end of a block.
  fclose(fp);

  printf("\033[1;32mWhat do you want to do now?\033[1;37m\n\n");
  printf("1)Store more information.\n\n2) Return home.\n\n3) View your information.\n\n\033[1;31m4) exit.\n\nchoice: \033[0m");

  scanf("%d", &choice);
  getchar();
  printf("\n\n");

  if (choice == 1)
  {
    storeInformation(username); // modified
  }
  else if (choice == 2)
  {
    main();
  }
  else if (choice == 3)
  {
    viewInformation(username); // modified
  }
  else if (choice == 4)
  {
    exit(0);
  }
  else
  {
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}

void updatePassword(char *username)
{
  FILE *fp1, *fp2;
  int targetAccount;       // the account no. that will be updated.
  int accountIterator = 1; // the file that is pointed by the pointer at a certain moment.
  char websiteAddress[100];
  char web[100] = "Website Address: ";
  char emailAddress[100];
  char email[100] = "Email Address: ";
  char *password;
  char takePass[100];
  char pass[100] = "Password: ";
  char line[1000];
  unsigned char *output;
  int lineNumber = 1;
  int flag = 0;
  int choice;
  unsigned char key[16];

  printf("Enter key: "); // getting the key
  fgets(key, sizeof(key), stdin);
  removeNewLine(key, strlen(key));
  int pl = padding(key); // purified key..

  // viewing the information
  fp1 = fopen(username, "r");
  if (fp1 == NULL)
  {
    printf("\033[1;31mCANN'T OPEN THE FILE!\n\n\033[0m");
    exit(1);
  }
  while (fgets(line, sizeof(line), fp1))
  {
    if ((lineNumber - 2) % 5 && strncmp(line, "-----", 5))
    {
      output = invCipher(line, output, key);
      line[0] = '\0';
      bytesToString(output, line); // here since output is pointer it shouldn't work properly.
      hexToString(line, line);
      free(output);
    }
    if (lineNumber > 1)
    {
      printf("%s\n", line);
    }
    lineNumber++;
  }
  fclose(fp1);

  lineNumber = 1; // because it will be needed further and it is necessary its value is one

  printf("Account you want to upgrade: ");
  scanf("%d", &targetAccount);
  getchar();
  printf("\n");

  printf("Updated website address: ");
  scanf("%s", websiteAddress);
  getchar();
  strcat(web, websiteAddress);
  printf("\n");

  printf("Updated email address: ");
  scanf("%s", emailAddress);
  getchar();
  strcat(email, emailAddress);
  printf("\n");

  printf("1) give password\n\n2) generate password\n\nchoice = ");
  scanf("%d", &choice);
  getchar();
  printf("\n");

  if (choice == 1)
  {
  again:
    scanf("%s", takePass);
    getchar();

    if (checkStrength(takePass, strlen(takePass)))
    {
      password = takePass;
    }
    else
    {
      goto again;
    }
  }
  else
  {
    password = generatePassword(password);
  }

  strcat(pass, password);

  // now starts the new file loading phase.
  fp1 = fopen(username, "r");
  if (fp1 == NULL)
  {
    printf("Cann't find the file.\n\n");
    exit(1);
  }
  fp2 = fopen("temp.txt", "a");
  if (fp2 == NULL)
  {
    printf("Cann't create the file.\n\n");
    exit(1);
  }
  // it seems like the first line isn't getting printed. so i think here i might add another line to manually add that line.
  while (fgets(line, sizeof(line), fp1))
  {
    if ((lineNumber - 2) % 5 == 0 && atoi(line) != 0)
    {
      accountIterator = atoi(line);
    }
    if (accountIterator == targetAccount && !flag)
    {
      fprintf(fp2, "%d.\n", accountIterator);

      output = cipher(web, output, key);
      bytesToString(output, web); // flag
      fprintf(fp2, "%s\n", web);
      free(output);

      output = cipher(email, output, key);
      bytesToString(output, email); // flag
      fprintf(fp2, "%s\n", email);
      free(output);

      output = cipher(pass, output, key);
      bytesToString(output, pass); // flag
      fprintf(fp2, "%s\n", pass);
      free(output);

      fprintf(fp2, "---------------------------------------------------------------------\n");
      flag = 1;
    }
    else if (accountIterator != targetAccount)
    {
      fprintf(fp2, "%s", line);
    }

    lineNumber++;
  }

  fclose(fp1);
  fclose(fp2);

  if (remove(username))
  { // false if successful
    perror("Error deleting the file!\n\n");
    exit(1);
  }
  // removed the the file with the backdated data.

  if (rename("temp.txt", username))
  { // false if successful
    perror("Erron occured while renaming!\n\n");
    exit(1);
  }
  logIn(username);
}

void viewInformation(char *username)
{
  FILE *fp;
  int choice;
  int lineNumber = 1;
  unsigned char line[1000];
  unsigned char *output;
  unsigned char key[16];

  // here getting new line from the buffer.
  printf("Enter key: "); // getting the key
  fgets(key, sizeof(key), stdin);
  removeNewLine(key, strlen(key));
  int pl = padding(key); // purified key..

  printf("\033[1;34mAll the information of this user: %s\n\n\033[0m", username);

  fp = fopen(username, "r");
  if (fp == NULL)
  {
    printf("\033[1;31mCANN'T OPEN THE FILE!\n\n\033[0m");
    exit(1);
  }
  while (fgets(line, sizeof(line), fp))
  {
    if ((lineNumber - 2) % 5 && strncmp(line, "-----", 5))
    {
      output = invCipher(line, output, key);
      line[0] = '\0';
      bytesToString(output, line);
      hexToString(line, line);
      free(output);
    }
    if (lineNumber > 1)
    {
      printf("%s\n", line);
    }
    lineNumber++;
  }

  fclose(fp);

  printf("\033[1;31m\n\nWHAT DO YOU WANT TO DO NOW?\n\n\033[0m");
  printf("\033[1;37m1) Return home.\n\n2) Store information.\n\n\033[1;31m3) exit.\n\n4) update information.\n\n\033[0;32mchoice: ");
  scanf("%d", &choice);
  getchar();
  printf("\n\n");

  if (choice == 1)
  {
    main();
  }
  else if (choice == 2)
  {
    storeInformation(username);
  }
  else if (choice == 3)
  {
    exit(0);
  }
  else if (choice == 4)
  {
    updatePassword(username);
  }
  else
  {
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}

void createAccount()
{
  FILE *fp;
  int choice;
  char *password;      // flag
  char password_2[53]; // flag
  unsigned char key[16];
  char username[20];

  printf("username:");
  scanf("%s", username);
  getchar();
  printf("\n\n");
  strcat(username, ".txt");

  printf("\033[0;37m1.Generate Password.\n\n2.Give Password.\033[0;31m(character:6-52)\n\n\033[0;37mChoice: \033[0m");
  scanf("%d", &choice);
  getchar();
  printf("\n\n");

  if (choice == 1)
  {
    password = generatePassword(password);
    fp = fopen(username, "a");
    if (fp == NULL)
    {
      printf("Error while opening file.\n");
      exit(1);
    }
    fprintf(fp, "%s\n", password);
    fclose(fp);
  }
  else if (choice == 2)
  {
  Again:
    printf("\033[0;32mPassword(length should be between 6 to 52): \033[0m");
    scanf("%s", password_2);
    getchar();
    printf("\n\n");

    if (strlen(password_2) < 6 || strlen(password_2) > 52)
    {
      printf("\033[0;31mYou didn't follow the rule.\n\n\033[0m");
      goto Again;
    }

    int strength = checkStrength(password_2, strlen(password_2));
    if (strength == 0)
    {
      goto Again;
    }
    else
    {
      fp = fopen(username, "a");
      if (fp == NULL)
      {
        printf("Error while opening file.\n");
        exit(1);
      }
      fprintf(fp, "%s\n", password_2);
      fclose(fp);
    }
  }
  else
  {
    printf("\x1b[31m");
    printf("Wrong command!\n");
    printf("\x1b[0m");
  }
  main();
}

int checkStrength(char *password, int length)
{
  if (length < 6 || length > 52)
  {
    printf("\033[1;31mYOUR PASSWORD LENGTH ISN'T WITHING 6-52.\n\n\033[0m");
    return -7;
  }
  int count = 0;
  if (length >= 8 && length < 10)
  {
    count++;
  }
  else if (length >= 10 && length < 16)
  {
    count += 2;
  }
  else
  {
    count += 3;
  }
  for (int i = 0; i < length; i++)
  {
    if (((int)password[i] >= 33 && (int)password[i] <= 47) || ((int)password[i] >= 58 && (int)password[i] <= 64) || ((int)password[i] >= 91 && (int)password[i] <= 96) || ((int)password[i] >= 123 && (int)password[i] <= 126))
    {
      count++;
      break;
    }
  }
  for (int i = 0; i < length; i++)
  {
    if ((int)password[i] >= 48 && (int)password[i] <= 57)
    {
      count++;
      break;
    }
  }
  for (int i = 0; i < length; i++)
  {
    if ((int)password[i] >= 65 && (int)password[i] <= 90)
    {
      count++;
      break;
    }
  }
  for (int i = 0; i < length; i++)
  {
    if ((int)password[i] >= 97 && (int)password[i] <= 122)
    {
      count++;
      break;
    }
  }
  if (count == 7)
  {
    printf("\x1b[32m");
    printf("Strong\n\n");
    printf("\x1b[0m");
    return 2;
  }
  else if (count >= 5 && count < 7)
  {
    printf("\x1b[33m");
    printf("medium\n\n");
    printf("\x1b[0m");
    return 1;
  }
  else if (count < 5)
  {
    printf("\x1b[31m");
    printf("weak\n\n");
    printf("\x1b[0m");
    return 0;
  }
}

char *customLengthPass(char *password)
{
  int length, i;
  printf("\033[1;37mLength of your password \033[1;31m(length must be between 6 to 52):\033[0m ");
  scanf("%d", &length);
  getchar();
  printf("\n\n");
  length++;
  password = malloc((length) * sizeof(char));
  for (i = 0; i < length - 1; i++)
  {
    password[i] = (char)(rand() % 93 + 33);
  }
  password[i] = '\0';
  return password;
}

char *randomLengthPass(char *password)
{
  int length, i;
  length = rand() % 46 + 6;
  password = malloc(length * sizeof(char));
  for (i = 0; i < length - 1; i++)
  {
    password[i] = (char)(rand() % 93 + 33);
  }
  password[i] = '\0';
  return password;
}

char *generatePassword(char *password)
{
  int choice;
  // srand(time(NULL));//this won't be needed sinse main method holds it
  printf("\033[1;37mDo you want to determine the length of the password?\n\n1)\033[1;32mYes.\033[0m\n\n0)\033[0;31mNo.\033[0m\n\nchoice: ");
  scanf("%d", &choice);
  getchar();
  printf("\n\n");
  if (choice == 1)
  {
    password = customLengthPass(password);
  }
  else if (choice == 0)
  {
    password = randomLengthPass(password);
  }
  else
  {
    printf("wrong command!\n");
  }
  printf("\033[1;37mYOUR GENERATED PASS WORD IS: %s\n\n\033[0m", password);
  return password;
}

void removeNewLine(char *str, int size)
{
  if (size > 0 && str[size - 1] == '\n')
  {
    str[size - 1] = '\0';
  }
}

void purifyKey(unsigned char *input)
{
  int length = strlen(input);
  unsigned char padd[16];
  unsigned char *state;
  int i;
  int paddLength = 16 - length % 16;
  for (i = 0; i < paddLength; i++)
  {
    padd[i] = ' ';
  }
  padd[i] = '\0';
  strcat(input, padd); // padding done

  unsigned char hexString[strlen(input) * 2 + 1];
  stringToHex(input, hexString);
  stringToBytes(hexString, input); // string to bytes done
  printf("check if worked parameter input: %s\n", input);
  printf("check what i wanted: %02x\n", input[0]);
}

void upload(char *username)
{
  int choice;
  printf("1) Generate Key.\n2) Upload file.(Without RSA Encryption)\n3) Upload file.(With RSA encryption)\nchoice: ");
  scanf("%d", &choice);
  getchar();
  if (choice == 1)
  {
    keyGenerator();
    logIn(username);
  }
  else if (choice == 2)
  {
    uploadToServer(username);
    // viewInformation(username); // this might need to change.
  }
  else if (choice == 3)
  {
    FILE *fin, *fout;
    long n, e;
    char line[300];
    char file[3000] = "";
    long encoded[3000];
    int lineNumber = 1;
    char filename[50] = "RSA";
    char password[100];

    printf("Please enter public key: \n");
    printf("n = ");
    scanf("%ld", &n);
    getchar();

    printf("e = ");
    scanf("%ld", &e);
    getchar();

    strcat(filename, username);

    if ((fin = fopen(username, "r")) == NULL)
    {
      printf("error opening file");
      exit(1);
    }
    fgets(password, sizeof(password), fin);
    // strcat(file,password);
    while (fgets(line, sizeof(line), fin))
    {
      strcat(file, line); // loaded the file.
    }
    fclose(fin);                  // closed input file.
    encoder(file, encoded, n, e); // encoded.

    if ((fout = fopen(filename, "w")) == NULL)
    {
      perror("error opening file in write mode.");
      exit(1);
    }
    fprintf(fout, "%s", password);
    for (int i = 0; i < strlen(file); i++)
    {
      fprintf(fout, "%ld,", encoded[i]);
    }

    fclose(fout);
    uploadToServer(filename);
  }
}