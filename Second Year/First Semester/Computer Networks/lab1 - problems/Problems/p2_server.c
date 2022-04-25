#include <stdio.h>
#include <WinSock2.h>
#include <stdint.h>

#pragma warning (disable:4996)

#define PORT 2500
#define DIM 256

int initializeWindowsSocketsLib();
void releaseWindowsSocketsLib();

int createSocket(SOCKET* s);
int countSpaces(char* str);

/*
int main(int argc, char** argv) {
	SOCKET server_socket;
	struct sockaddr_in server, client;

	if (initializeWindowsSocketsLib())
		return -1;
	if (createSocket(&server_socket))
		return -1;

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("Binding error");
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

		printf("...client connected from: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		int n = 0;
		int rec = recv(client_sfd, (char*)&n, sizeof(n), 0);
		if (rec != sizeof(n)) {
			printf("Error at receiving array length!\n");
			closesocket(client_sfd);
			continue;
		}

		n = ntohl(n);
		printf("...received n = %d from client\n", n);

		char str[DIM];
		rec = recv(client_sfd, str, n * sizeof(char), 0);
		str[n] = '\0';

		if (rec != n * sizeof(char)) {
			printf("Error at receiving string from client!\n");
			closesocket(client_sfd);
			continue;
		}

		int spaces = htonl(countSpaces(str));
		printf("...sending %d to the client\n", ntohl(spaces));
		if (send(client_sfd, (char*)&spaces, sizeof(spaces), 0) != sizeof(spaces)) {
			printf("Error sending spaces no to the client!\n");
		}

		closesocket(client_sfd);
	}	

	releaseWindowsSocketsLib();
	return 0;
}
*/

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

int countSpaces(char* str)
{
	int cnt = 0;
	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == ' ')
			cnt++;
	}

	return cnt;
}
