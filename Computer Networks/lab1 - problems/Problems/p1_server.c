#include <stdio.h>

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define closesocket close
typedef int SOCKET;

#else
#include <WinSock2.h>
#include <stdint.h>
#endif

#define PORT 2500

int initWindowsSocketLib();
void releaseWindowsSocketLib();

SOCKET createSocket();
int bindSocket(SOCKET socket, struct sockaddr_in* server);

int main(int argc, char **argv) {
	struct sockaddr_in server, client;

	if (initWindowsSocketLib() < 0)
		return -1;

	SOCKET server_fd = createSocke();
	memset(&server, 0, sizeof(server));

	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bindSocket(server_fd, &server) < 0)
		return -1;
	listen(server_fd, 5);

	while (1) {
		memset(&client, 0, sizeof(client));
		int client_size = sizeof(client);

		printf("...waiting for a client to connect\n");
	}

	return 0;
}

int initWindowsSocketLib() {
#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
		printf("Error while initializing the Windows Sockets Library!\n");
		return -1;
	}
#endif

	return 0;
}

void releaseWindowsSocketLib() {
#ifdef WIN32
	WSACleanup();
#endif
}

SOCKET createSocket() {
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Error while creating socket!\n");
		return -1;
	}
	return s;
}

int bindSocket(SOCKET socket, struct sockaddr_in* server) {
	if (bind(socket, (struct sockaddr*) server, sizeof(*server)) < 0) {
		printf("Error while binding the socket!\n");
			return -1;
	}
	return 0;
}
