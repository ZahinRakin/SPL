#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE 1024

void sendFile(int sockfd)
{
    FILE *fp;
    char filename[100];
    char password[100];
    char file[30000];
    char line[100];
    int e;

    read(sockfd, filename, sizeof(filename)); // read the filename.
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("file doesn't exist.\n");
        write(sockfd, "FALSE", 5); // response if the doesn't exist.
        close(sockfd);
        return;
    }
    write(sockfd, "TRUE", 4); // response if the file exist.

    read(sockfd, password, sizeof(password)); // reading the password after sending the authentication.

    fgets(file, 100, fp);
    if (strncmp(file, password, strlen(file) - 1))
    {
        printf("authentication failed\n");
        write(sockfd, "FALSE", 5); // response if the pass don't match.
        close(sockfd);
        return;
    }
    printf("authentication successful\n");
    write(sockfd, "TRUE", 4); // response if the pass match.
    // now start file transfering.
    while (fgets(line, sizeof(line), fp))
    {
        strcat(file, line);
    } // whole file is inside the file string.

    printf("%s\n", file);

    e = write(sockfd, file, strlen(file)); // sending the file to the server.
    printf("bytes sent: %d\n", e);
    close(sockfd);
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

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

    sendFile(new_sock);
    printf("[+]Data written in the text file ");
}