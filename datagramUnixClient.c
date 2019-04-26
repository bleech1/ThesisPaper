/*
 * datagramUnixClient.c
 */

// This program connects to a datagram UNIX domain socket

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

    // set up the destination socket
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, socketPath);

    struct sockaddr *ptr = (struct sockaddr *) &addr;
    int len = sizeof(addr);

    int bytesRead = 10;
    char buf[100];
    int retVal;
    while (bytesRead > 0)
    {
        // read in from stdin and send
        bytesRead = read(0, buf, 100);
        if (bytesRead < 0)
        {
            perror("read");
            exit(1);
        }
        retVal = sendto(sockFd, buf, bytesRead, 0, ptr, len);
        if (retVal < 0)
        {
            perror("sendto");
            exit(1);
        }
    }
    int ret = close(sockFd);
    if (ret < 0)
    {
        perror("close");
        exit(1);
    }

}
