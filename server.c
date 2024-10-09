#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    const char *ip_address = "127.0.0.1";
	int val;
	char user_ID[100];
	int pass;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

	inet_pton(AF_INET, ip_address, &address.sin_addr);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    printf("Waiting for connections on %s:%d...\n", ip_address, PORT);

	const char *firstMenu = "Enter log-in type: \n 1. Customer \n 2. Bank Employee \n 3. Manager \n 4. Administrator \n 5. Exit \n Enter your choice : ";

	while(1) {
		new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

		int processId = fork();

		if(processId == 0) {
			while(1) {
				send(new_socket, firstMenu, strlen(firstMenu), 0);

				read(new_socket, &val, sizeof(val));

				if(ntohl(val)==5)
					break;

				printf("Menu item selected : %d\n", ntohl(val));
			}
			printf("Client has Terminated");
			close(new_socket);
			break;
		}
		else {
			close(new_socket);
		}
	}

    return 0;
}
