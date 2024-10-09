#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65000
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client";
    char buffer[BUFFER_SIZE];
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

    while(1) {
		memset(buffer, 0, sizeof(buffer));
		read(sock, buffer, BUFFER_SIZE);
		printf("%s", buffer);

		scanf("%d", &val);
		val = htonl(val);

		send(sock, &val, sizeof(val), 0);
		if(ntohl(val)==5)
			break;

	}

    close(sock);
    return 0;
}
