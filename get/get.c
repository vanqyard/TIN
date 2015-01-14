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
	printf("result = %d\n", result);

	receiveIPAddresses();

	return 0;
}

int receiveIPAddresses() {
	int sock;
	int perm = 1;
	struct sockaddr_in addr;
	int numbytes;
	MSG_CFD message;

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf("sock() failed");
		return -1;
	} else printf("sock() ok");

	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &perm, sizeof(addr)) < 0) {
		printf("setsockopt() failed");
		return -1;
	} else printf("setsockopt() ok");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(DAEMON_PORT);
	addr.sin_addr.s_addr = inet_addr(INADDR_ANY);

	if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		printf("bind() failed");
		return -1;
	} else printf("bind() ok");

	if((numbytes=recvfrom(sock, &message, sizeof(MSG_CFD), 0, NULL, NULL)) < 0) {
		printf("recvfrom() failed");
		return -1;
	} else printf("recvfrom() ok");

	printf("%d \n", numbytes);

	close(sock);

	return numbytes;
}

int sendToBroadcast(MSG* message) {
	int sock;
	struct sockaddr_in addr;
	int numbytes;
	int perm = 1;

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		return -1;
	}

	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &perm, sizeof(addr)) < 0) {
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(DAEMON_PORT);
	addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

	if((numbytes=sendto(sock, message, sizeof(MSG), 0,
			(struct sockaddr*)&addr, sizeof(addr))) < 0) {

		return -1;
	}

	close(sock);

	return numbytes;
}
