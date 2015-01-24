#include "daemon.h"

int doListen()
{
	int sock, number, result;
	socklen_t length;
	struct MSG *msg;
	struct sockaddr_in thisAddr, thatAddr;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	bzero(&thisAddr, sizeof(thisAddr));
	thisAddr.sin_family = AF_INET;
	thisAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	thisAddr.sin_port = htons(DAEMON_PORT);

	bind(sock, (struct sockaddr*)&thisAddr, sizeof(thisAddr));

	msg = malloc(sizeof(struct MSG));

	while(1) {
		number = recvfrom(sock, msg, sizeof(struct MSG), 0, (struct sockaddr *)&thatAddr, &length);
		printf("IP: %s\n", inet_ntoa(thatAddr.sin_addr));
		printf("recieved: %d\n", number);

		sleep(1);

		switch(msg->flag) {
			case CFR :
				printf("CFR!!!\n");
				result = sendConfFileData(msg, sock, &thatAddr, length);
				printf("bytes CFD sent %d \n", result);
				break;
			case PFR :
				printf("PFR!!!\n");
				result = sendPortFileData(msg, sock, &thatAddr, length);
				printf("bytes PFD sent %d \n", result);
				break;
		}

		break;
	}

	return 0;
}
