#include "daemon.h"
#include "../lib.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int doListen(int sock, struct sockaddr* pcliaddr, socklen_t clilen)
{
	int n, fd;
	socklen_t len;
	MSG message;

	while(1) {
		len = clilen;

		n = recvfrom(sock, &message, sizeof(MSG), 0, pcliaddr, &len);
		if(n != sizeof(MSG)) {
			continue;
		}

		switch(message.flag) {
			case FLAG_CFR :
				printf("cfr \n");
				break;
			case FLAG_PFR :
				printf("pfr \n");
				break;
		}
	}

	return 0;
}
