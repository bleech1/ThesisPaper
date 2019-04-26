/*
 * datagramLocalhostServer.c
 */

// This program creates a datagram Internet socket over localhost

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

int main(int argc, char *argv[])
{
    // create the socket
    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
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
    hints.ai_socktype = SOCK_DGRAM;
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

    int readResult = 10;
    char buf[100];
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        // accept each connection and read the first message sent then close
        readResult = recvfrom(sockFd, buf, sizeof(buf), 0, NULL, 0);
        if (readResult < 0)
        {
            perror("recvfrom");
            exit(1);
        }
        printf("Received: %s", buf);
    }
}


