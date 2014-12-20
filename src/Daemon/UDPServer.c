#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../Common/Secure.c"
#define PACKET_SIZE 100
char* port = "2002";			// ocal port/service
struct addrinfo *servAddr;		// List of server addresses

int main(int argc, char *argv[]) {

	// Construct the server address structure
	struct addrinfo addrCriteria;						// Criteria for address
	memset(&addrCriteria, 0, sizeof(addrCriteria));		// Zero out structure
	addrCriteria.ai_family = AF_UNSPEC;					// Any address family: IP4 or IP6
	addrCriteria.ai_flags = AI_PASSIVE;					// For wildcard IP address: accept on any address/port
	addrCriteria.ai_socktype = SOCK_DGRAM;				// Only datagram socket
	addrCriteria.ai_protocol = IPPROTO_UDP;				// Only UDP socket (0 if any protocol)

	Getaddrinfo(NULL, port, &addrCriteria, &servAddr);		// (NULL, port, &hints, &result)

	// Create socket for incoming connections
	int sock = Socket(servAddr->ai_family, 
						servAddr->ai_socktype, 
							servAddr->ai_protocol);
	
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
		char buffer[PACKET_SIZE]; // I/O buffer

		// Size of received message
		ssize_t numBytesRcvd = recvfrom(sock, buffer, PACKET_SIZE, 0, (struct sockaddr *) &clntAddr, &clntAddrLen);

		if (numBytesRcvd < 0)
			DieWithSystemMessage("recvfrom() failed");
		
		fputs("Handling client ", stdout);
		PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
		fputc('\n', stdout);
	
		// Send received datagram back to the client
		ssize_t numBytesSent = sendto(sock, buffer, numBytesRcvd, 0, (struct sockaddr *) &clntAddr, sizeof(clntAddr));

		if (numBytesSent < 0)
			DieWithSystemMessage("sendto() failed)");
		else if (numBytesSent != numBytesRcvd)
			DieWithUserMessage("sendto()", "sent unexpected number of bytes");
	}
	// NOT REACHED
}