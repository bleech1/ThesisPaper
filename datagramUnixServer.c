/*
 * datagramUnixServer.c
 */

// This program makes a datagram UNIX domain socket
// with a name

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
    int sockFd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockFd < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    int size = sizeof(addr.sun_path);
    strncpy(addr.sun_path, socketPath, size - 1);
    unlink(socketPath);

    // remove the socket if it exists
    int unlinkVal = unlink(socketPath);

    // bind the socket to the pathname
    int size = sizeof(addr);
    int retVal = bind(sockFd, (struct sockaddr*) &addr, size);
    if (retVal < 0)
    {
        perror("bind");
        exit(1);
    }

    int res = 0;
    char buf[100];
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        // read and print every message sent
        res = recvfrom(sockFd, buf, sizeof(buf), 0, NULL, 0);
        if (res < 0)
        {
            perror("recvfrom");
            exit(1);
        }
        printf("Received: %s", buf);
    }
}
