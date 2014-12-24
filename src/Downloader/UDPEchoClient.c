#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../Common/Secure.c"
//#include "../Common/PrintSocketAddr.c"
//#include "../Common/DieWithMessage.c"
#define PACKET_SIZE 100

void SetUDPSocketCriteria(struct addrinfo* addrCriteria);
char *server = "127.0.0.1";									// server address/name
char *echoString = "idiots everywhere"; 					// word to echo
char *servPort = "2002";									// Third arg (optional): server port/service
int bytesCounter = 0;
ssize_t numBytes;

int main(int argc, char *argv[]) {
	size_t echoStringLen = strlen(echoString);				// size of message
	
	//if (echoStringLen > PACKET_SIZE) 			// Check input length
	//	DieWithUserMessage(echoString, "string too long");
	
	// Construct the server address structure
	struct addrinfo addrCriteria;							// Criteria for address
	SetUDPSocketCriteria(&addrCriteria);

	struct addrinfo *servAddr; // List of server addresses
	int rtnVal = Getaddrinfo(server, servPort, &addrCriteria, &servAddr);

	// Create a datagram/UDP socket
	int sock = Socket(servAddr->ai_family, 
					  servAddr->ai_socktype, 
					  servAddr->ai_protocol); // Socket descriptor for client



	
	//while(bytesCounter != 0) {
		// Send the string to the server
		numBytes = sendto(sock, 
						  echoString, 
						  echoStringLen, 
						  0, 
						  servAddr->ai_addr, 
						  servAddr->ai_addrlen);

		if (numBytes < 0)
			DieWithSystemMessage("sendto() failed");
		else if (numBytes != echoStringLen)
			DieWithUserMessage("sendto() error", "sent unexpected number of bytes");
	//}
	
	// Receive a response
	struct sockaddr_storage fromAddr; // Source address of server

	// Set length of from address structure (in-out parameter)
	socklen_t fromAddrLen = sizeof(fromAddr);

	char buffer[PACKET_SIZE + 1]; 					// I/O buffer
	numBytes = recvfrom(sock, 
						buffer, 
						PACKET_SIZE, 
						0,
						(struct sockaddr *) &fromAddr, 
						&fromAddrLen);

	if (numBytes < 0)
		DieWithSystemMessage("recvfrom() failed");
	else if (numBytes != echoStringLen)
		DieWithUserMessage("recvfrom() error", "received unexpected number of bytes");

	// Verify reception from expected source
	//if (!SockAddrsEqual(servAddr->ai_addr, (struct sockaddr *) &fromAddr))
	//	DieWithUserMessage("recvfrom()", "received a packet from unknown source");
	
	freeaddrinfo(servAddr);
	buffer[echoStringLen] = '\0';

	// Null-terminate received data
	printf("Received: %s\n", buffer); // Print the echoed string
	close(sock);
	exit(0);
}

void SetUDPSocketCriteria(struct addrinfo* addrCriteria) {
	memset(addrCriteria, 0, sizeof(*addrCriteria));
	
	addrCriteria->ai_family = AF_UNSPEC;
	addrCriteria->ai_socktype = SOCK_DGRAM;
	addrCriteria->ai_protocol = IPPROTO_UDP;	
}
