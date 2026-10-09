#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd == -1) {
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
	struct sockaddr_in cliente;
	char msg[100];
	char cliente_addr[16];
	do {
		socklen_t cliente_len = sizeof(cliente);
		int rvf = recvfrom(socket_fd, msg, sizeof(msg) -1, 0, (struct sockaddr*)&cliente, &cliente_len);
		if(rvf == -1) {
			perror("RECV ERR");
			return 1;
		}else if(rvf == 0) {
			printf("o cliente se desconectou\n");
		}
		msg[rvf] = '\0';
		printf("%s\n", msg);
		int prt = ntohs(cliente.sin_port);
		int in_np = inet_ntop(AF_INET, &cliente.sin_addr, cliente_addr, sizeof(cliente_addr));
		if(in_np == NULL) {
			perror("INET_NTOP ERR");
			return 1;
		}
		printf("porta:%i\n", prt);
		printf("endereço:%s\n", cliente_addr);
	}while(1);
}
