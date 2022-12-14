//main function for a command line command of type download ftp://ftp.up.pt/pub/...

#include <stdio.h>
#include <stdlib.h>
#include "clientTCP.c"
#include "URLparser.c"


int main (int argc, char *argv[]) {

    //Check if usage is correct and display if not

    if (argc != 3) {
        fprintf(stderr, "Usage: download <URL from which to download file \n URL format according to RFC1738: ftp://[<user>:<password@]<host>/<url-path> \n");
        exit(-1);
    }

    int sockfd;

    struct URL url;

    //parse URL to get details

    if (parseURL(argc, argv, &url)) {
        exit(0);
        printf("Error occured while parsing URL\n");
        return 1;
    }

    //connect to the ftp server and check for errors

    if (newSocket(url.ip, 21, &sockfd)) {
        printf("Error occured while creating socket\n");
        return 1;
    }

   /*  //open the socket for sending commands and reading responses

    FILE *socket = fdopen(sockfd, "r");

    //initial response from server

    if (readReply(socket)) {
        printf("Error occured while reading initial response from server\n");
        return 1;
    }

    char buf[1024];

    //send the user command

    //assign "user %S\n" to buf

    snprintf(buf, sizeof(buf), "user %s\n", user);  //this user should come from the output of the URL parser

    if (sendCommand(sockfd, buf)) {
        printf("Error occured while sending user command\n");
        return 1;
    }

    //read the response from the server

    if (readReply(socket)) {
        printf("Error occured while reading response from server\n");
        return 1;
    }

    //send the password command

    //assign "pass %S\n" to buf

    snprintf(buf, sizeof(buf), "pass %s\n", passs);  //this pass should come from the output of the URL parser

    //send the passive mode command 

    //assign "pasv\n" to buf

    snprintf(buf, sizeof(buf), "pasv \n"); 

    if (sendCommand(sockfd, buf)) {
        printf("Error occured while sending passive mode command\n");
        return 1;
    }

    //CALCULATE IP AND PORT FROM PASV RESPONSE

    char ip[32];
    int port;

    if (readResponsePassive (socket, ip, &port)) {
        printf("Error occured while reading response from server in passive mode\n");
        return 1;
    }

    //init connection to server on ip and portt to start transfering files

    if (newSocket(ip, port, &newsockfd)) {
        printf("Error occured while creating socket\n");
        return 1;
    }

    //send the retr command to retrieve the file from the specified path

    //assign "retr %S\r\n" to buf

    snprintf(buf, sizeof(buf), "retr %s\r\n", path);  //this path should come from the output of the URL parser

    if (sendCommand(sockfd, buf)) {
        printf("Error occured while sending retr command\n");
        return 1;
    }

    //read the response from the server

    if (readReply(newsockfd)) {
        printf("Error occured while reading response from server\n");
        return 1;
    }

    //write the contents to a new file with the same name as the file in the path

    FILE *file = fopen(path, "w");  //this path should come from the output of the URL parser

    if(file == NULL){
        printf("Error opening file\n");
        return 1;
    }   

    //read byte by byte from the socket and write to the file

    char *c = malloc(1);
    if (c == NULL)
    {
        printf("Error allocating memory\n");
        return 1;
    }
    
    while(read(newsockfd, c, 1) > 0){  // read one byte at a time
        fputc(*c, file);
    }

    free(c);
    fclose(file);
 */
    return 0;
}