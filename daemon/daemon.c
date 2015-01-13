/*
 * daemon.c
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../lib.h"
#include "daemon.h"
#include "sf_dae.c"

int daemonMain(int argc, char **argv) {
	pid_t pid = 0;
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
	close(STDERR_FILENO);

	/* ====[ network ]==== */

	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family			= AF_INET;
	servaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	servaddr.sin_port 			= htons(DAEMON_PORT);

	bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	sf_dae(sockfd, (struct sockaddr*) &cliaddr, sizeof(cliaddr));

	//while(1) {
		//sleep(PERIOD);
		//doListen();
	//}

	return 0;
}

void doListen() {
	int sockfd;
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
}

void doSend() {

}
