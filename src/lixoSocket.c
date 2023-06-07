#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
	struct sockaddr_in caddr;
	struct sockaddr_in saddr  = {
			.sin_family 		= AF_INET,
			.sin_addr.s_addr 	= htonl(INADDR_ANY),
			.sin_port			= htons(5000)
	};

	int server = socket(AF_INET, SOCK_STREAM, 0);

	bind(server, (struct sockaddr *) &saddr, sizeof saddr);

	listen(server, 5);

	int csize = sizeof caddr;
	int cliente;
	char buff[150];

	while (1) {
		accept(server, (struct sockaddr *) &caddr, &csize);
		recv(cliente, buff, sizeof buff, 0);

		printf("\nMensagem recebida, %s", buff);

		pclose(cliente);

		return 0;
	}
}
