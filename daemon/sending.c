#include "daemon.h"

void sendConfFileData(MSG_CFR *confFileRequest, int sock, struct sockaddr_in *address, socklen_t length) {
	printf("CFD\n");
}

void sendPortFileData(MSG_PFR *portFileRequest, int sock, struct sockaddr_in *address, socklen_t length) {
	printf("PFD\n");
}
