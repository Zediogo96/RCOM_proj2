#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int getIP(char *host, char* IPaddress) {
    struct hostent *h;

    if ((h = gethostbyname(host)) == NULL) {
        herror("gethostbyname()");
        return -1;
    }

    strcpy(IPaddress, inet_ntoa(*((struct in_addr *) h->h_addr)));

    printf("Host name  : %s\n", h->h_name);
    printf("IP Address : %s\n", IPaddress);

    return 0;
}
