#include "daemon.h"

int doListen(int sock, struct sockaddr_in *address, socklen_t length)
{
	int n, result;
	MSG message;
	MSG_CFR confFileRequest;
	MSG_PFR portFileRequest;

	while(1) {
		n = recvfrom(sock, &message, sizeof(MSG), 0, (struct sockaddr *)address, &length);

		switch(message.flag) {
			case FLAG_CFR :
				memcpy(&confFileRequest, &message, sizeof(MSG));
				result = sendConfFileData(&confFileRequest, sock, address, length);
				break;
			case FLAG_PFR :
				memcpy(&portFileRequest, &message, sizeof(MSG));
				result = sendPortFileData(&portFileRequest, sock, address, length);
				break;
		}

		printf("result: %d\n", result);
	}

	return 0;
}
