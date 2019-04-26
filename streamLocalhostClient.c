/*
 * streamLocalhostClient.c
 */

// This program connects to a stream Internet socket over localhost

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define PORT "50000"
#define IP_ADDR "localhost"

int main(int argc, char *argv[])
{
    // create the socket
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket");
        exit(1);
    }

    struct addrinfo hints;
    struct addrinfo *res;
    int rc;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if((rc = getaddrinfo(IP_ADDR, PORT, &hints, &res)) != 0)
    {
        printf("getaddrinfo failed: %s\n", gai_strerror(rc));
        exit(1);
    }

    // Connect to server
    if(connect(sockFd, res->ai_addr, res->ai_addrlen) < 0)
    {
        perror("connect");
        exit(1);
    }

    int bytesRead = 10;
    char buf[100];
    // read in from stdin and send
    bytesRead = read(0, buf, 100);
    if (bytesRead < 0)
    {
        perror("read");
        exit(1);
    }
    int retVal = send(sockFd, buf, bytesRead, 0);
    if (retVal < 0)
    {
        perror("send");
        exit(1);
    }
    int ret = close(sockFd);
    if (ret < 0)
    {
        perror("close");
        exit(1);
    }

}

