/*
 * datagramLocalhostClient.c
 */

// This program connects to a datagram Internet
// socket over localhost

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
#define IP_ADDR "127.0.0.1"

int main(int argc, char *argv[])
{
    // create the socket
    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockFd < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(atoi(PORT)); 
    inet_pton(AF_INET, IP_ADDR, &servaddr.sin_addr); 

    struct sockaddr *ptr = (struct sockaddr *) &servaddr;
    int size = sizeof(struct sockaddr);

    int bytesRead = 10;
    char buf[100];
    // read in from stdin and send
    bytesRead = read(0, buf, 100);
    if (bytesRead < 0)
    {
        perror("read");
        exit(1);
    }
    int retVal = sendto(sockFd, buf, bytesRead, 0, ptr, size);
    if (retVal < 0)
    {
        perror("sendto");
        exit(1);
    }
    int ret = close(sockFd);
    if (ret < 0)
    {
        perror("close");
        exit(1);
    }

}


