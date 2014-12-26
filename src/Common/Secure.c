#include "PrintSocketAddr.c"
#include "DieWithMessage.c"

int Socket(int domain, int type, int protocol) {

	// Create socket for incoming connections
	int sock = socket(domain, type, protocol);

	if (sock < 0)
		DieWithSystemMessage("socket() failed");
	
	return sock;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	
	// Bind to the local address
	int retVal = bind(sockfd, addr, addrlen);
	
	if (retVal < 0)
		DieWithSystemMessage("bind() failed");

	return retVal;
}

void Freeaddrinfo(struct addrinfo *res) {
	freeaddrinfo(res);
}

int Getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints, struct addrinfo **res) {

	int retVal = getaddrinfo(node, service, hints, res);

	if (retVal != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(retVal));

	return retVal;
}

ssize_t Recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen) {

	ssize_t numBytesRcvd = recvfrom(sockfd, 
									buf, 
									len, 
									flags, 
									src_addr, 
									addrlen);

	if (numBytesRcvd < 0)
		DieWithSystemMessage("recvfrom() failed");
		
	return numBytesRcvd;
}

ssize_t Sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen) {
	
	ssize_t numBytesSent = sendto(sockfd, 
								  buf, 
								  len, 
								  flags, 
								  dest_addr, 
								  addrlen);
	
	if (numBytesSent < 0)
		DieWithSystemMessage("sendto() failed)");

	return numBytesSent;
}








