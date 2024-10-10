#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65001
#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

void FillLoginDetails(int socketfd) {
	memset(buffer, 0, BUFFER_SIZE);

	read(socketfd, buffer, BUFFER_SIZE);
	
	printf("%s", buffer);

	memset(buffer, 0, BUFFER_SIZE);
	
	fgets(buffer, BUFFER_SIZE, stdin);

	send(socketfd, buffer, strlen(buffer), 0);

	memset(buffer, 0, BUFFER_SIZE);

	read(socketfd, buffer, BUFFER_SIZE);
	printf("%s", buffer);

	memset(buffer, 0, BUFFER_SIZE);

	fgets(buffer, BUFFER_SIZE, stdin);

	send(socketfd, buffer, strlen(buffer), 0);
}

void GetWelcomeMenu(int socketfd) {
	memset(buffer, 0, BUFFER_SIZE);

	read(socketfd, buffer, BUFFER_SIZE);
	printf("%s", buffer);

	memset(buffer, 0, BUFFER_SIZE);

	int val, response;
	scanf("%d", &val);
	getchar();

	response = htonl(val);

	send(socketfd, &response, sizeof(response), 0);

	if(val >= 1 && val <= 4) {
		FillLoginDetails(socketfd);
	}
	else if(val == 5) {
		return;
	}
	else {
		GetWelcomeMenu(socketfd);
	}
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
	const char *ip_address = "127.0.0.1";
	int val;

	sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, ip_address, &serv_addr.sin_addr);

    int success = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	if(success == -1) {
		printf("Issues while connecting to the server.\n");
		close(sock);
		return 0;
	}

    
	GetWelcomeMenu(sock);

    close(sock);
    return 0;
}