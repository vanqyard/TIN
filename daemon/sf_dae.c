#include "../lib.h"

void
sf_srv(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen)
{
	int 		n, fd;
	socklen_t 	len;
	msg			message;

	for( ; ; ) {
		len = clilen;

		n = recvfrom(sockfd, &message, sizeof(msg), 0, pcliaddr, &len);

		switch(message.flag) {

			case FLAG_CFR :				/* żądanie odczytu */
				printf("cfr \n");
				break;
			case FLAG_CFD :
				printf("cfd \n");
				break;
			case FLAG_PFR :
				printf("pfr \n");
				break;
			case FLAG_PFD :
				printf("pfd \n");
				break;
		}
	}
}
