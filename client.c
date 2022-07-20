#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#define max 100
#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main()
{
    int sockfd;
    struct sockaddr_in serverAddress;

    // initializations
    int n1, n2, ans;
    char msg[max], op;

    // sockfd
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // memset
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);

    connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    while (1)
    {
        printf("Enter equation: \n");
        gets(msg);
        n1 = msg[0] - '0';
        op = msg[1];
        n2 = msg[2] - '0';

        write(sockfd, &op, 10);
        write(sockfd, &n1, sizeof(n1));
        write(sockfd, &n2, sizeof(n2));

        printf("sent equation\n");

        read(sockfd, &ans, sizeof(ans));
    }

    return 0;
}
