#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
int main() {
	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr destino;
	destino.
