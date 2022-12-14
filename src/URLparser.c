#include "URLparser.h"

#define MAX_URL_SIZE 256

int parseURL(int argc, char *argv[], URL *url) {

    if (strncmp(argv[2], "ftp://", 6) != 0) {
        fprintf(stderr, "Error: not using FTP.\n\n");
        exit(-1);
    }

    // Parse the first argument to get the host and path
    sscanf(argv[2], "ftp://%[^/]/%s", url->host, url->path);

    // Parse the host string to get the user and password
    sscanf(url->host, "%[^:]:%[^@]@%[^/]", url->user, url->password, url->host);

    // If password is empty, use default values for user and password
    if(strlen(url->password)==0) {
        strcpy(url->user, "anonymous");
        strcpy(url->password, "apple123");
    }

    printf("\nUser: %s\nPwd: %s\nHost: %s\nPath: %s\n", url->user, url->password, url->host, url->path);
    
    return 0;
}
