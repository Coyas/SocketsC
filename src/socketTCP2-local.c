#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>

int main() {
  // Create a socket.
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Bind the socket to an address.
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8081);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  // Listen for connections.
  if (listen(sockfd, 10) < 0) {
	printf("Listen for connection");
    perror("listen");
    exit(1);
  }

  // Accept a connection.
  int clientfd = accept(sockfd, NULL, NULL);
  if (clientfd < 0) {
    perror("accept");
    exit(1);
  }

  // Send and receive data.
  char buffer[1024];
  int nread;
  while ((nread = read(clientfd, buffer, sizeof(buffer))) > 0) {
	printf("recebido: %s", buffer);
    write(clientfd, buffer, nread);
  }

  // Close the sockets.
  close(sockfd);
  close(clientfd);

  return 0;
}

