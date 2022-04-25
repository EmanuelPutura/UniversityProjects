/*
#include <stdio.h>
#include <WinSock2.h>
#include <cstdint>

#define PORT 2500
#pragma warning (disable:4996)

int initializeWindowsSocketsLib();
void releaseWindowsSocketsLib();

int createSocket(SOCKET *socket); 
int receiveIntFromClient(int client_sfd);

int main(int argc, char** argv) {
	SOCKET server_socket;
	struct sockaddr_in server, client;

	if (initializeWindowsSocketsLib()) return -1;;
	if (createSocket(&server_socket)) return 1;


	memset(&server, 0, sizeof(server));
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_socket, (struct sockaddr*) &server, sizeof(server)) < 0) {
		perror("Bind error");
		return 1;
	}
	
	listen(server_socket, 5);
	memset(&client, 0, sizeof(client));
	int client_size = sizeof(client);

	while (1) {
		printf("...listening for incoming connections\n");
		int client_sfd = accept(server_socket, (struct sockaddr*)&client, &client_size);
		int err = errno;

		#ifdef WIN32
		err = WSAGetLastError();
		#endif

		if (client_sfd < 0) {
			printf("Accept error: %d\n", err);
			continue;
		}

		printf("...incoming connected client from: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		
		// serving the connected client
		int n = receiveIntFromClient(client_sfd);
		if (n == -1) continue;

		int sum = 0;
		for (int i = 0; i < n; ++i) {
			int current = receiveIntFromClient(client_sfd);
			sum += current;
		}

		printf("...sending %d to the client\n", sum);
		sum = htonl(sum);
		if (send(client_sfd, (char*)&sum, sizeof(sum), 0) != sizeof(sum)) {
			printf("Error sending result to the client!\n");
		}

		closesocket(client_sfd);
	}

	releaseWindowsSocketsLib();
	return 0;
}

int initializeWindowsSocketsLib() {
#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
		printf("Error initializing the Windows Sockets LIbrary!\n");
		return -1;
	}
	return 0;
#endif
}

void releaseWindowsSocketsLib() {
#ifdef WIN32
	WSACleanup();
#endif
}

int createSocket(SOCKET* s) {
	*s = socket(AF_INET, SOCK_STREAM, 0);
	if (*s < 0) {
		printf("Error at socket creation!\n");
		return 1;
	}
	return 0;
}

int receiveIntFromClient(int client_sfd) {
	int n = 0;
	int rec = recv(client_sfd, (char*)&n, sizeof(n), 0);
	if (rec != sizeof(n)) {
		printf("Error receiving array length!\n");
		return -1;
	}

	printf("...received %d from client\n", n);
	// return ntohl(n);
	return n;
}
*/