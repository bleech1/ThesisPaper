/*
 * streamUnixServer.c
 */

// This program makes a stream UNIX domain socket with a name

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
    unlink(socketPath);

    // remove the socket if it exists
    int unlinkVal = unlink(socketPath);

    // bind the socket to the pathname
    int retVal = bind(sockFd, (struct sockaddr*) &addr, sizeof(addr));
    if (retVal < 0)
    {
        perror("bind");
        exit(1);
    }

    // listen for incoming connections
    retVal = listen(sockFd, 10);
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
