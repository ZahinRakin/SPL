#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1000

void removenewline(char str[])
{ // this works for sure.
  if (str[strlen(str) - 1] == '\n')
  {
    str[strlen(str) - 1] = '\0';
  }
}

int main()
{
  FILE *fp;
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
  char filename[30];
  char password[53];
  char ok[] = "OK";
  char nok[] = "NOT_OK";

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created. \n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (e < 0)
  {
    perror("[-]Error in Binding");
    exit(1);
  }
  printf("[+]Binding Successfull.\n");

  e = listen(sockfd, 10);
  if (e == 0)
  {
    printf("[+]Listening...\n");
  }
  else
  {
    perror("[-]Error in Binding");
    exit(1);
  }
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
  // end.....
  if (recv(new_sock, filename, sizeof(filename), 0) <= 0)
  {
    perror("recv\n");
    exit(1);
  }
  if (recv(new_sock, password, sizeof(password), 0) <= 0)
  {
    perror("recv\n");
    exit(1);
  }
  printf("%s + %s\n", filename, password); ////
  if ((fp = fopen(filename, "r")) == NULL)
  {
    printf("NO SUCH FILE.\n");
    exit(1);
  }
  fgets(buffer, sizeof(buffer), fp);
  removenewline(buffer);
  if (strcmp(password, buffer) != 0)
  {
    printf("password didn't match.\n");
    if (send(new_sock, nok, sizeof(nok), 0) == -1)
    {
      perror("send\n");
      exit(1);
    }
  }
  else
  {
    printf("password matched!\n");
    if (send(new_sock, ok, sizeof(ok), 0) == -1)
    {
      perror("send\n");
      exit(1);
    }

    rewind(fp);
    bzero(buffer, sizeof(buffer));
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
      printf("%s", buffer);
      // removenewline(buffer);//test...
      if (send(new_sock, buffer, strlen(buffer), 0) == -1)
      {
        perror("send\n");
        exit(1);
      }
      bzero(buffer, sizeof(buffer));
    }
  }
  printf("[+]Data sent to the client ");
}