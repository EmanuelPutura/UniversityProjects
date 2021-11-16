#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define MAX_CHARS 16384
#define MAX_THREADS 24
#define SLEEP 5

struct ThreadWorkerArg {
    struct sockaddr_in client;
    int client_sock;
    int index;
};

void checkCommandLineArgs(int argc, char** argv);

int createSocket();
void bindSocket(int sock, struct sockaddr_in *server);

void *threadWorker(void *arg);

int main(int argc, char **argv) {
    checkCommandLineArgs(argc, argv);

    struct sockaddr_in server, client;
    memset(&server, 0, sizeof(server));

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_family = AF_INET;

    int server_sock = createSocket();
    bindSocket(server_sock, &server);
    listen(server_sock, 5);

    pthread_t threads[MAX_THREADS];
    int threads_no = 0;

    while (1) {
        memset(&client, 0, sizeof(client));
        int client_size = sizeof(client);
        
        printf("...waiting for clients to connect\n");
        int client_sock = accept(server_sock, (struct sockaddr*) &client, &client_size);

        struct ThreadWorkerArg *arg = malloc(sizeof(struct ThreadWorkerArg));
        arg->client = client;
        arg->client_sock = client_sock;
        arg->index = threads_no + 1;

        pthread_create(&threads[threads_no++], NULL, threadWorker, (void*) arg);
    }

    for (int i = 0; i < threads_no; ++i)
        pthread_join(threads[i], NULL);
    
    close(server_sock);
    return 0;
}

void *threadWorker(void *arg) {
    struct sockaddr_in client = ((struct ThreadWorkerArg*) arg)->client;
    int client_sock = ((struct ThreadWorkerArg*) arg)->client_sock;
    int index = ((struct ThreadWorkerArg*) arg)->index;
    printf("...thread %d started working for client %s : %d\n", index, inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    sleep(SLEEP);
    printf("...client %s : %d is done waiting\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    int32_t len;
    if (recv(client_sock, &len, sizeof(len), 0) != sizeof(len)) {
        printf("Error while receiving string length from client %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        return NULL;
    }

    len = ntohl(len);
    char file_path[MAX_CHARS], output[MAX_CHARS];
    recv(client_sock, file_path, sizeof(char) * len, 0);

    // if (recv(client_sock, file_path, sizeof(char) * len, 0) != sizeof(char) * len) {
    //     printf("Error while receiving string from client %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    //     return NULL;
    // }

    printf("...received file path '%s' from client %s : %d\n", file_path, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    
    char command[MAX_CHARS] = "cat ";
    strcat(command, file_path);

    FILE *fp = popen(command, "r");
    while (fgets(output + strlen(output), MAX_CHARS, fp) != NULL);
    
    output[strlen(output)] = '\0';
    int exit_code = pclose(fp);
    
    len = exit_code == 0 ? strlen(output) : -1;
    printf("...sending number %d to client %s : %d\n", len, inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    len = htonl(len);
    if (send(client_sock, &len, sizeof(len), 0) != sizeof(len)) {
        printf("Error while sending data to client %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        return NULL;
    }

    len = ntohl(len);
    if (len == -1)
        return NULL;

    len++;
    if (send(client_sock, output, sizeof(char) * len, 0) != sizeof(char) * len) {
        printf("Error while sending data to client %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        return NULL;
    }

    printf("...client %s : %d finished its work\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    return NULL;
}

void checkCommandLineArgs(int argc, char **argv) {
    if (argc != 2) {
        printf("%s <port>\n", argv[0]);
        exit(-1);
    }
}

int createSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Error while creating the socket!\n");
        exit(-1);
    }
    return sock;
}

void bindSocket(int sock, struct sockaddr_in *server) {
    if (bin