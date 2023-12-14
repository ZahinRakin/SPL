#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SIZE 1024


int main(){
    char filename[80];
    FILE *fp;
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("Error in socket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("Error in bind");
    exit(1);
  }

  if(listen(sockfd, 10) == 0){
	}else{
		perror("Error in listening");
    exit(1);
	}

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

//basic preparation ended.

  if(read(new_sock,filename,sizeof(filename)) < 0){
    perror("cann't read");
    exit(1);
  }

  if((fp = fopen(filename, "a")) == NULL){
    // perror("error occured while opening file.");
    // exit(1);
  }
  fprintf(fp,"hello world");


  //my desired operation.

  return 0;
}