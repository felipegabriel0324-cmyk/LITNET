#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
int main() {
	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd == -1) {
		perror("SOCKET ERR");
		return 1;
	}
	struct sockaddr_in destino;
	destino.sin_family = AF_INET;
	destino.sin_port = htons(9999);
	int in_pt = inet_pton(AF_INET, "10.35.220.18", &destino.sin_addr);
	if(in_pt == 0) {
		perror("INET_PTON ERR");
		return 1;
	}else if(in_pt == -1) {
		perror("INET_PTON ERR");
		return 1;
	}
	int con = connect(socket_fd, (struct sockaddr *)&destino, sizeof(destino));
	if(con == -1) {
		perror("CONNECT ERR");
		return 1;
	}
	char msg[100];
	do {
		printf("Digite a mensagem a ser enviada, digite nada e o programa encerrara\n");
		fgets(msg, 99, stdin);
		msg[strcspn(msg, "\n")] = '\0';
		int sd = send(socket_fd, msg, strlen(msg), 0);
		if(sd == -1) {
			perror("SEND ERR");
			return 1;
		}
	}while(msg[0]);
	return 0;
}
