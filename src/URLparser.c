#include "../include/URLparser.h"

#define MAX_URL_SIZE 256

int parseURL(int argc, char *argv[], URL *url)
{

    char temp_path[128];

    if (strncmp(argv[1], "ftp://", 6) != 0)
    {
        fprintf(stderr, "Error: not using FTP.\n\n");
        exit(-1);
    }

    strcpy(url->user, "\0");
    strcpy(url->password, "\0");

    // Parse the first argument to get the host and path
    sscanf(argv[1], "ftp://%[^/]/%s", url->host, url->path);

    // Parse the host string to get the user and password
    sscanf(url->host, "%[^:]:%[^@]@%[^/]", url->user, url->password, url->host);

    // If password is empty, use default values for user and password
    if (strlen(url->password) == 0)
    {
        strcpy(url->user, "anonymous");
        strcpy(url->password, "apple123");
    }

    printf("\nUser: %s\nPwd: %s\nHost: %s\nPath: %s\n", url->user, url->password, url->host, url->path);

    if (getIP(url->host, url) != 0)
    {
        printf("Error getting host name\n");
        return 1;
    }

    // extract the file name from the path
    strcpy(temp_path, url->path);
    char *token2 = strtok(temp_path, "/");
    while (token2 != NULL)
    {
        strcpy(url->filename, token2);
        token2 = strtok(NULL, "/");
    }

    return 0;
}

int getIP(char *host, URL *url)
{
    struct hostent *h;

    if ((h = gethostbyname(host)) == NULL)
    {
        herror("gethostbyname()");
        return 1;
    }

    printf("\nIP Address : %s\n\n", inet_ntoa(*((struct in_addr *)h->h_addr)));

    strcpy(url->ip, inet_ntoa(*((struct in_addr *)h->h_addr)));

    return 0;
}

void getPortPlusIp(int *port, char *ip, FILE *socket)
{
    char *fullString = NULL;
    size_t numBytes;

    int foundLine = 0;
    
    while (foundLine == 0)
    {
        getline(&fullString, &numBytes, socket);
        if (strstr(fullString, "227 Entering Passive Mode") != NULL)
        {
            foundLine = 1;
        }
    }

    int ip1, ip2, ip3, ip4, port1, port2;

    sscanf(fullString, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)", &ip1, &ip2, &ip3, &ip4, &port1, &port2);

    sprintf(ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);

    *port = port1 * 256 + port2;
}
