#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1) {
		perror("Socket_fd Error");
		return 1;
	}
	struct sockaddr_in destino;
	destino.sin_family = AF_INET;
	destino.sin_port = htons(9999);
	int in_pt = inet_pton(AF_INET, "192.168.1.3", &destino.sin_addr);
	if(in_pt == 0) {
		fprintf(stderr, "Endereço IP invalido\n");
		return 1;
	}else if(in_pt == -1) {
		fprintf(stderr, "Familia de Endereços invalida");
		return 1;
	}
	int con = connect(socket_fd, (struct sockaddr *)&destino, sizeof(destino));
	if(con == -1) {
		perror("connect Error");
		return 1;
	}
	char msg[100];
	int exit = 0;
	char msgtemp[100];
		do {
			fgets(msg, 99, stdin);
			msg[strcspn(msg, "\n")] = '\0';
			for(int i = 0;i<5;i++) {
				strcpy(msgtemp, msg);
				strcat(msg, msgtemp);
			}
			int sd = send(socket_fd, msg, strlen(msg), 0);
			//for(int i = 0;i<5;i++) {
				//send(socket_fd, msg, strlen(msg), 0);
			//}
			if(sd == -1) {
				fprintf(stderr, "Send Error");
				return 1;
			}
			if(strcmp(msg, "exit\n") == 0) {
				exit = 1;
			}
		}while(exit != 1);
		return 0;
}
