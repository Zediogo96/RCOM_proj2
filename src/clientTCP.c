#include "../include/clientTCP.h"

// Create a new socket and connect it to an address and port

int newSocket(char *address, int port, int *sockfd)
{

    struct sockaddr_in server_addr;

    /*server address handling*/
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(address); /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(port);               /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket()");
        exit(-1);
    }

    /*connect to the server*/
    if (connect(*sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect()");
        exit(-1);
    }
    return 0;
}

// reads reply from tcp socket connection
int readReply(FILE *socket)
{
    char *reply = NULL;
    long code;
    char *end_pointer;
    size_t reply_size = 0;

    // read from socket while there is content, exit with code 1 if error found
    while (getline(&reply, &reply_size, socket) > 0)
    {
        printf("%s\n", reply);
        if (reply[3] == ' ')
        {
            code = strtol(reply, &end_pointer, 10);
            if (code >= 500 && code <= 559)
            {
                printf("Error code: %ld\n", code);
                exit(1);
            }
            break;
        }
        reply_size += strlen(reply);
        reply = realloc(reply, reply_size);
    }
    return 0;
}

// sends a command over a socket connection
int sendCommand(int sockfd, char *cmd)
{

    // Use ssize_t instead of int for the bytesSent variable
    // to match the return type of the write() function.

    ssize_t bytesSent = write(sockfd, cmd, strlen(cmd));

    if (bytesSent < 0)
    {
        perror("Error sending command");
        return 1;
    }

    return 0;
}

int readResponsePassive(FILE *socket, char (*ip)[], int *port)
{
    char *buf = NULL;
    size_t bytesRead = 0;

    while (1)
    {
        getline(&buf, &bytesRead, socket);
        printf("%s", buf);
        if (buf[3] == ' ')
        {
            break;
        }
    }

    int ip1, ip2, ip3, ip4, port1, port2;
    if (sscanf(buf, "(%d,%d,%d,%d,%d,%d)", &ip1, &ip2, &ip3, &ip4, &port1, &port2) != 6)
    {
        printf("\nError while parsing the IP parts and ports. \n");
    }

    // Use snprintf() to prevent buffer overflows
    snprintf(*ip, 16, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);

    // Use the parsed values directly as integers
    *port = port1 * 256 + port2;

    return 0;
}

int writeToFile(char *fileN, int socket)
{   

    struct stat st = {0};

    // Create the "downloads" directory if it doesn't already exist.
    if (stat("downloads", &st) == -1) {
        mkdir("downloads", 0700);
    }

    // Concatenate the directory and file names to create the full file path.
    char filePath[256];
    sprintf(filePath, "downloads/%s", fileN);

    FILE *file = fopen(filePath, "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    char *c = malloc(1);
    if (c == NULL)
    {
        printf("Error allocating memory\n");
        return 1;
    }

    int numRead;
    while ((numRead = read(socket, c, 1)) > 0)
    { // read one byte at a time
        if (fputc(*c, file) == EOF)
        {
            printf("Error writing to file\n");
            return 1;
        }
    }
    if (numRead < 0)
    {
        printf("Error reading from socket\n");
        return 1;
    }

    free(c);
    fclose(file);
    return 0;
}
