/*
 * daemon.c
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../lib.h"
#include "daemon.h"

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

	while(1) {
		//sleep(PERIOD);
		listen();
	}

	return 0;
}

void listen() {
}

void send() {
}
