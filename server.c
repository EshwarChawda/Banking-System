#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65001
#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

void GetCredentialsFromClient(int socketfd){
	send(socketfd, loginIdLabel, loginIdLabelLength, 0);

	memset(buffer, 0, BUFFER_SIZE);
	read(socketfd, buffer, BUFFER_SIZE);

	char loginId[100];
	char password[100];

	strcpy(loginId, buffer);

	send(socketfd, passwordLabel, passwordLabelLength, 0);

	memset(buffer, 0, BUFFER_SIZE);
	read(socketfd, buffer, BUFFER_SIZE);

	strcpy(password, buffer);

	memset(buffer, 0, BUFFER_SIZE);
}

int SendWelcomeMenu(int socketfd) {
	// Sending the Predefined Welcome Menu to the client
	send(socketfd, clientMenu, clientMenuLength, 0);

	// Waiting for the response from the client
	int responseValue;

	read(socketfd, &responseValue, sizeof(responseValue));

	responseValue = ntohl(responseValue);

	// Responding to the client as per the Selected Menu Item
	switch (responseValue)
	{
		case 1: GetCredentialsFromClient(socketfd);
			break;
		
		case 2:
			break;
		
		case 3:
			break;
		
		case 4:
			break;
		
		case 5: 
			break;
		
		default: SendWelcomeMenu(socketfd);
			break;
	}

	return 0;
}

int main() {
	init();

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

	inet_pton(AF_INET, serveripAddress, &address.sin_addr);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

	signal(SIGCHLD, SIG_IGN);

    printf("Waiting for connections on %s:%d...\n", serveripAddress, PORT);

	while(1) {
		new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

		int processId = fork();

		if(processId == 0) {
			SendWelcomeMenu(new_socket);
			close(new_socket);
			close(server_fd);
			exit(0);
		}
		else {
			close(new_socket);
		}
	}

    return 0;
}