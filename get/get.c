/*
 * get.c
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../lib.h"
#include "get.h"

int getMain(int argc, char **argv) {
	MSG message;
	int result;

	//memcpy(buffer, 0, 512);
	message.flag = FLAG_CFR;

	result = sendToBroadcast(&message);
	printf("%d\n", result);

	return 0;
}

int sendToBroadcast(MSG* message) {
	int sock;
	struct sockaddr_in addr;
	int numbytes;
	int perm = 1;

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		return 1;
	}

	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &perm, sizeof(addr)) < 0) {
		return 2;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(DAEMON_PORT);
	addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

	if((numbytes=sendto(sock, message, sizeof(MSG), 0, &addr, sizeof(addr))) < 0) {
		return 3;
	}

	close(sock);

	return 0;
}
