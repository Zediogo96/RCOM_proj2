

#include "clientTCP.h"

//Create a new socket and connect it to an address and port

int newSocket(char *address, int port, int *sockfd) {

    struct sockaddr_in server_addr;

    /*server address handling*/
    memset((char *) &server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(address);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(port);        /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(-1);
    }
    
    /*connect to the server*/
    if (connect(*sockfd, (struct sockaddr *) &server_addr,  sizeof(server_addr)) < 0) {
        perror("connect()");
        exit(-1);
    }
    return 0;
}


//sends a command over a socket connection

// int sendCommand(int sockfd, const char* cmd, size_t size) {

//     size_t bytes;

//     if ((bytes = write(sockfd, cmd, size)) < 0) {
//         perror("Write error in sendCommand");
//         return (-1);
//     }

//     printf("Bytes sent: %ld\n", bytes);

//     return 0;

// }

// //reads reply from tcp socket conncetion

// int readReply(FILE* socket) {
//     char* reply;
//     ints code;
//     char* end_pointer;
//     size_t reply_size = 0;

//     //read from socket while there is content, exit with code 1 if error found

//     while (getline(&reply, &reply_size, socket) > 0) {
//         printf("%s", reply);
//         if (reply[3] == ' ') {
//             code = strtol(reply, &end_pointer, 10);
//             if (code >= 500 && code <= 559) {
//                 printf("Error code: %d\n", code);
//                 exit(1);
//             }
//             return 0;
//         }
        
//     }
    
// }


// int readResponsePassive(FILE *socket, char (*ip)[], int *port){

//     char * buf;
// 	size_t bytesRead = 0;

//     while (1){
//         getline(&buf, &bytesRead, socket);
//         printf("%s", buf);
//         if (buf[3] == ' '){
//             break;
//         }
//     }

//   strtok(buf, "(");       
//   char* ip1 = strtok(NULL, ",");       // 193
//   char* ip2 = strtok(NULL, ",");       // 137
//   char* ip3 = strtok(NULL, ",");       // 29
//   char* ip4 = strtok(NULL, ",");       // 15

//   sprintf(*ip, "%s.%s.%s.%s", ip1, ip2, ip3, ip4);
  
//   char* p1 = strtok(NULL, ",");       // 199
//   char* p2 = strtok(NULL, ")");       // 78

//   *port = atoi(p1)*256 + atoi(p2);
  
//   return 0;
// }
