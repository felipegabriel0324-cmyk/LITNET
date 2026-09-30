#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd == 0) {
		perror("SOCKET ERR");
		return 1;
	}
	struct sockaddr_in servidor;
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(9999);
	int in_pt = inet_pton(AF_INET, "127.0.0.1", &servidor.sin_addr);
	if(in_pt == 0) {
		perror("INET_PTON ERR");
		return 1;
	}else if(in_pt == -1) {
		perror("INET_PTON ERR");
		return 1;
	}
	int bd = bind(socket_fd, (struct sockaddr *)&servidor, sizeof(servidor));
	if(bd == -1) {
		perror("BIND ERR");
		return 1;
	}
	int lis = listen(socket_fd, 1);
	if(lis == -1) {
		perror("LISTEN ERR");
		return 1;
	}
	struct sockaddr_in cliente;
	socklen_t cliente_len = sizeof(cliente);
	int cliente_fd = accept(socket_fd, (struct sockaddr*)&cliente, &cliente_len);
	if(cliente_fd == -1) {
		perror("ACCEPT ERR");
		return 1;
	}
	char msg[100];
	do {
		int rv = recv(socket_fd, msg, 100, 0);
		if(rv == -1) {
			perror("RECV ERR");
			return 1;
		}else if(rv == 0) {
			printf("Conexão encerrada\n");
			return 0;
		}
		if(rv == 100) {
			msg[rv -1] = '\0';
		}else{
			msg[rv] - '\0';
		}
		printf("%s\n", msg);
	}while(1);
}
