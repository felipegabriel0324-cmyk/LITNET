#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main() {
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1) {
		perror("Socket_fd Error");
		return 1;
	}
	struct sockaddr_in servidor;
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(9999);
	int in_pt = inet_pton(AF_INET, "192.168.1.3", &servidor.sin_addr);
	if(in_pt == 0) {
		fprintf(stderr, "Endereço IP invalido\n");
		return 1;
	}else if(in_pt == -1) {
		fprintf(stderr, "Familia de Endereços invalida");
		return 1;
	}
	int bd = bind(socket_fd, (struct sockaddr *)&servidor, sizeof(servidor));
	if(bd == -1) {
		fprintf(stderr, "Bind Error");
		return 1;
	}
	int lis = listen(socket_fd, 1);
	if (lis == -1) {
		fprintf(stderr, "Listen Error");
		return 1;
	}
	struct sockaddr_in cliente;
	socklen_t cliente_len = sizeof(cliente);
	int cliente_fd = accept(socket_fd, (struct sockaddr *)&cliente, &cliente_len);
	if(cliente_fd == -1) {
		fprintf(stderr, "Accept Error");
		return 1;
	}
	char msg[100];
	do {
		int rv = recv(cliente_fd, msg, 100, 0);
		if(rv == -1) {
			fprintf(stderr, "Recv Error");
			return 1;
		}else if(rv == 0) {
			printf("Conexão encerrada");
			return 0;
		}
		if(rv == 100) {
			msg[rv -1] = '\0';
		}
		else {
			msg[rv] = '\0';
		}
		printf("%s\n", msg);
	}while(1);
}
