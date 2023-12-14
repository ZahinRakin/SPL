#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void send_file(FILE *fp, int sockfd){
  int n;
  char data[1000] = {0};

  while(fgets(data, sizeof(data), fp) != NULL) {
    if (write(sockfd, data, sizeof(data)) < 0) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, sizeof(data));
  }
}

void download(int new_sock){//user wants to download. not the server. naming is little confusing.
    FILE *fp;
    char filename[100];
    char password[100];
    char line[1000];
    if(read(new_sock, filename, sizeof(filename)) < 0){
        perror("error with reading.");
        exit(1);
    }
    
    if(read(new_sock, password, sizeof(password)) < 0){
        perror("error with reading.");
        exit(1);
    }
    //reading filename and password done.

    if((fp = fopen(filename, "r")) == NULL){
        perror("file doesn't exist.");
        exit(1);
    }
    //opened file in read mode.

    fgets(line, sizeof(line), fp);//read the password.
    //remove new line
    if(line[strlen(line)-1] == '\n'){
        printf("yes new line found... inside server download\n");//test
        line[strlen(line)-1] = '\0';
    }
    //removed new line
    if(!strcmp(password,line)){//check if the password is correct or not.
        //send file.
        send_file(fp,new_sock);
        close(new_sock);
    }else {
        printf("wrong credentials!\n");
        close(new_sock);
    }

}

void upload(){
    printf("Under construction.");
}

int main(){
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;
    char choice[10];

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    

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
    //basic structure
    if(read(new_sock, choice, sizeof(choice)) < 0){
        perror("reading");
        exit(1);
    }
    if(choice[0] == '1'){
        download(new_sock);
        close(new_sock);
    }else if(choice[0] == '2'){
        upload(new_sock);
        close(new_sock);
    }

}