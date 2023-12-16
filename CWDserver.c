#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define SA struct sockaddr

void sendFile(int sockfd)
{
    FILE *fp;
    char filename[100];
    char password[100];
    char file[30000];
    char line[100];
    char res[5];
    int e;

    read(sockfd, filename, sizeof(filename));
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
    read(sockfd, res, 4);
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
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    sendFile(connfd);
}
