/*
 * streamLocalhostServer.c
 */

// This program creates a stream Internet socket over localhost

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT "50000"
#define IP_ADDR "localhost"
#define BACKLOG 10

int main(int argc, char *argv[])
{
    // create the socket
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket");
        exit(1);
    }

    // Bind it to a port
    struct addrinfo hints;
    struct addrinfo *res;
    int rc;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if((rc = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        printf("getaddrinfo failed: %s\n", gai_strerror(rc));
        exit(1);
    }

    int retVal = bind(sockFd, res->ai_addr, res->ai_addrlen);
    if (retVal < 0)
    {
        perror("bind");
        exit(1);
    }

    // Start listening
    retVal = listen(sockFd, BACKLOG);
    if (retVal < 0)
    {
        perror("listen");
        exit(1);
    }

    int readResult = 10;
    char buf[100];
    while (1)
    {
        // accept each connection and read the first message sent then close
        int clientFd = accept(sockFd, NULL, NULL);
        if (clientFd < 0)
        {
            perror("accept");
            continue;
        }
        readResult = recv(clientFd, buf, sizeof(buf), 0);
        if (readResult < 0)
        {
            perror("recv");
            exit(1);
        }
        printf("Received: %s", buf);
        memset(buf, 0, sizeof(buf));
        clientFd = close(clientFd);
        if (clientFd < 0)
        {
            perror("close");
            exit(1);
        }
    }
}

