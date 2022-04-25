#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

int main (int argc, char **argv) {
    if (argc != 4) {
        printf("arguments error: <server address> <port> <command>\n");
        exit(1);
    }

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        printf("Error while creating socket!\n");
        exit(1);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_fd, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Error while connecting to server!\n");
        exit(1);
    }

    printf("...sending %s to the server\n", argv[3]);
    
    int32_t len = strlen(argv[3]) + 1;
    len = htonl(len);
    if (send(client_fd, (char*) &len, sizeof(len), 0) != sizeof(len)) {
        printf("Error while sending string length to the server!\n");
        exit(1);
    }

    len = ntohl(len);

    printf("...sending command %s (length %d) to the server\n", argv[3], len);

    if (send(client_fd, argv[3], sizeof(char) * len, 0) != sizeof(char) * len) {
        printf("Error while sending command string to the server!\n");
        exit(1);
    }

    int32_t exit_code;
    if (recv(client_fd, (char*) &exit_code, sizeof(exit_code), 0) != sizeof(exit_code)) {
        printf("Error while receiving exit code from the server\n");
        exit(1);
    }

    printf("...received exit code %d from the server\n", ntohl(exit_code));
    len = 0;

    if (recv(client_fd, (char*) &len, sizeof(len), 0) != sizeof(len)) {
        printf("Error while receiving string length from the server\n");
        exit(1);
    }

    len = ntohl(len);
    char output[MAX_SIZE];

    if (recv(client_fd, output, sizeof(char) * len, 0) != sizeof(char) * len) {
        printf("Error while receiving command output string from the server\n");
        exit(1);
    }

    printf("...received command output %s from the server\n", output);
    
    close(client_fd);
    return 0;
}