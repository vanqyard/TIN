#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <openssl/md5.h>
#include "../Common/Secure.c"
#include "../Common/Filestat.c"
#define PACKET_SIZE 20

void fillBuffer(char* buffer, const char* content);
void SetUDPSocketCriteria(struct addrinfo* addrCriteria);
char* port = "2002";										// ocal port/service
struct addrinfo *servAddr;									// List of server addresses

int 
main(int argc, char *argv[]) {

	// Construct the server address structure
	struct addrinfo addrCriteria;
	SetUDPSocketCriteria(&addrCriteria);

	Getaddrinfo(NULL, port, &addrCriteria, &servAddr);

	// Create socket for incoming connections
	int sock = Socket(servAddr->ai_family, 
					  servAddr->ai_socktype, 
					  servAddr->ai_protocol);
	
	//int nonBlocking = 1;
	//	fcntl( sock, F_SETFL, O_NONBLOCK, nonBlocking );

	// Bind to the local address
	Bind(sock, servAddr->ai_addr, servAddr->ai_addrlen);

	// Free address list allocated by getaddrinfo()
	Freeaddrinfo(servAddr);

	for (;;) { // Run forever in real time loop
		// Client address
		struct sockaddr_storage clntAddr;

		// Set Length of client address structure (in-out parameter)
		socklen_t clntAddrLen = sizeof(clntAddr);

		// Block until receive message from a client
		char buffer[PACKET_SIZE]; 		// I/O buffer

		// Size of received message
		ssize_t numBytesRcvd = Recvfrom(sock, 
										buffer, 
										PACKET_SIZE, 
										0, 
										(struct sockaddr *) &clntAddr, 
										&clntAddrLen);
		
		//fprintf(stderr, "%d \n", numBytesRcvd);
		
		/** handle client **/
		
		fputs("Handling client ", stdout);
		PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
		fputc('\n', stdout);
		
		/*******************/

		//fillBuffer(buffer, "md5");
		
		// Send received datagram back to the client
		ssize_t numBytesSent = Sendto(sock, 
									  buffer, 
									  PACKET_SIZE,			//numBytesRcvd, 			//numBytesRcvd, 
									  0, 
									  (struct sockaddr *) &clntAddr, 
									  sizeof(clntAddr));
		
		//fprintf(stderr, "%d \n", numBytesSent);
	}
	
	// NOT REACHED
}

void SetUDPSocketCriteria(struct addrinfo* addrCriteria) {
	memset(addrCriteria, 0, sizeof(*addrCriteria));

	addrCriteria->ai_family = AF_UNSPEC;
	addrCriteria->ai_flags = AI_PASSIVE;
	addrCriteria->ai_socktype = SOCK_DGRAM;
	addrCriteria->ai_protocol = IPPROTO_UDP;	
}

void fillBuffer(char* buffer, const char* content) {
	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, content, 3);
}
