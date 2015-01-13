/*
 * daemon.c
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../lib.h"
#include "daemon.h"

int daemonMain(int argc, char **argv) {
	int sock;
	struct sockaddr_in serverAddr, clientAddr;
	/*pid_t pid = 0;
	pid_t sid = 0;

	pid = fork();
	if(pid < 0) {
		printf("Wystąpił nieokreślony błąd!\n");
		return 1;
	}

	else if(pid > 0) {
		printf("Uruchomiono proces w tle.\n");
		return 0;
	}

	sid = setsid();
	if(sid < 0) {
		printf("Wystąpił nieokreślony błąd!\n");
		return 1;
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO); */

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(DAEMON_PORT);

	bind(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
	doListen(sock, (struct sockaddr*) &clientAddr, sizeof(clientAddr));

	return 0;
}
