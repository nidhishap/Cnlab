#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#define MAX 100
#define PORT 8080

int main()
{
    int sockfd, newsockfd;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    // initialization
    int n1, n2, res, pid;
    int clientAddressLength;
    char op;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    listen(sockfd, 5);

    while (1)
    {
        printf("Connected to server\n");
        clientAddressLength = sizeof(clientAddress);
        newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddressLength);

        pid = fork();
        if (pid == 0)
        {
            while (1)
            {
                read(newsockfd, &op, 10);
                read(newsockfd, &n1, sizeof(n1));
                read(newsockfd, &n2, sizeof(n2));

                switch (op)
                {
                case '+':
                    res = n1 + n2;
                    break;
                case '-':
                    res = n1 - n2;
                    break;
                case '*':
                    res = n1 * n2;
                    break;
                case '/':
                    res = n1 / n2;
                    break;
                default:
                    break;
                }

                write(newsockfd, &res, sizeof(res));
                printf("answer is %d\n", res);
            }
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }

    return 0;
}
