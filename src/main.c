// main function for a command line command of type download ftp://ftp.up.pt/pub/...

#include <stdio.h>
#include <stdlib.h>
#include "../include/clientTCP.h"
#include "../include/URLparser.h"

int main(int argc, char *argv[])
{

    // Check if usage is correct and display if not
    if (argc != 2)
    {
        fprintf(stderr, "Usage: download <URL from which to download file \n URL format according to RFC1738: ftp://[<user>:<password@]<host>/<url-path> \n");
        exit(-1);
    }

    int sockfd, new_sock;
    struct URL url;

    // parse URL to get details
    if (parseURL(argv, &url))
    {
        exit(0);
        printf("Error occured while parsing URL\n");
        return 1;
    }

    // connect to the ftp server and check for errors

    if (newSocket(url.ip, 21, &sockfd))
    {
        printf("Error occured while creating socket\n");
        return 1;
    }

    // open the socket for sending commands and reading responses
    FILE *socket = fdopen(sockfd, "r");

    // initial response from server
    if (readReply(socket))
    {
        printf("Error occured while reading initial response from server\n");
        return 1;
    }

    char cmd[URL_MAX_SIZE + 8];
    // Log in to the FTP server using the provided username and password
    sprintf(cmd, "user %s\n", url.user);
    if (sendCommand(sockfd, cmd) != 0)
    {
        return 1;
    }
    if (readReply(socket) != 0)
    {
        return 1;
    }

    sprintf(cmd, "pass %s\n", url.password);
    if (sendCommand(sockfd, cmd) != 0)
    {
        return 1;
    }
    if (readReply(socket) != 0)
    {
        return 1;
    }

    // Enter passive mode and retrieve the server's IP and port
    sprintf(cmd, "pasv \n");
    if (sendCommand(sockfd, cmd) != 0)
    {
        return 1;
    }

    // CALCULATE PORT FROM PASV RESPONSE
    int port;

    calc_portAddress(&port, socket);

    // Connect to the server on the provided IP and port and retrieve the file
    if (newSocket(url.ip, port, &new_sock) != 0)
    {
        printf("Error starting connection\n");
        return 1;
    }

    sprintf(cmd, "retr %s\r\n", url.path); // retrieve file from path
    if (sendCommand(sockfd, cmd) != 0)
    {
        return 1;
    }
    if (readReply(socket) != 0)
    {
        return 1;
    }

    // Write the contents of the file to a local file with the same name
    if (writeToFile(url.filename, new_sock) != 0)
    {
        return 1;
    }

    // Quit the FTP session and close the connection
    sprintf(cmd, "quit \r\n");
    if (sendCommand(sockfd, cmd) != 0)
    {
        return 1;
    }

    printf("Download complete > program will now exit...\n\n");

    return 0;
}