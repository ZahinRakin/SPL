#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

int main(){
  char filename[80];
  printf("Enter file name: ");
  scanf("%s",filename);
  getchar();

  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }

//   fp = fopen(filename, "r");
//   if (fp == NULL) {
//     perror("[-]Error in reading file.");
//     exit(1);
//   }
//basic structure ended..

  if(write(sockfd, filename, sizeof(filename)) < 0){
    perror("error");
    exit(1);
  }

//desired function ended..

  close(sockfd);

  return 0;
}