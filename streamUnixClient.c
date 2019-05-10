/*
 * streamUnixClient.c
 */

// This program connects to a stream UNIX domain socket

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *socketPath = "named";
    
    // create the socket
    int sockFd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socketPath, sizeof(addr.sun_path)-1);

    // connect the socket to the listening socket
    int size = sizeof(addr);
    int retVal = connect(sockFd, (struct sockaddr*) &addr, size);
    if (retVal < 0)
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
    retVal = send(sockFd, buf, bytesRead, 0);
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
