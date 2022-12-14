//This file shoul be able to parse a URL into its components for use in FTP file transfer
//See RFC1738 for more information on URL syntax
//ftp://[<user>:<password@]<host>/<url-path>
//Should be included in the main file for the FTP client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL_SIZE 1000

int parseURL(int argc, char *argv[], char* path, char* host, char* user, char* pwd) {
    // Initialize user and password to empty strings
    user[0] = '\0'; pwd[0] = '\0';

    // Parse the first argument to get the host and path
    sscanf(argv[1], "ftp://%[^/]/%s", host, path);

    // Parse the host string to get the user and password
    sscanf(host, "%[^:]:%[^@]@%[^/]", user, pwd, host);

    // If password is empty, use default values for user and password
    if(strlen(pwd)==0){
        strcpy(user, "anonymous");
        strcpy(pwd, "default-pwd");
    }

    printf("\nuser: %s\npassword: %s\nhost: %s\npath: %s\n", user, pwd, host, path);
    
    return 0;
}

int main(int argc, char *argv[]) {
    
    char host[256]; char path[256]; char username[256]; char password[256];
    parseURL(argc, argv, path, host, username, password);

    return 0;
}