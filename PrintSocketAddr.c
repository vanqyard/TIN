<<<<<<< HEAD
/* Supported address families. */
#define AF_UNSPEC	0
#define AF_UNIX		1	/* Unix domain sockets 		*/
#define AF_INET		2	/* Internet IP Protocol 	*/
#define AF_AX25		3	/* Amateur Radio AX.25 		*/
#define AF_IPX		4	/* Novell IPX 			*/
#define AF_APPLETALK	5	/* Appletalk DDP 		*/
#define	AF_NETROM	6	/* Amateur radio NetROM 	*/
#define AF_BRIDGE	7	/* Multiprotocol bridge 	*/
#define AF_AAL5		8	/* Reserved for Werner's ATM 	*/
#define AF_X25		9	/* Reserved for X.25 project 	*/
#define AF_INET6	10	/* IP version 6			*/
#define AF_MAX		12	/* For now.. */

/* Protocol families, same as address families. */
#define PF_UNSPEC	AF_UNSPEC
#define PF_UNIX		AF_UNIX
#define PF_INET		AF_INET
#define PF_AX25		AF_AX25
#define PF_IPX		AF_IPX
#define PF_APPLETALK	AF_APPLETALK
#define	PF_NETROM	AF_NETROM
#define PF_BRIDGE	AF_BRIDGE
#define PF_AAL5		AF_AAL5
#define PF_X25		AF_X25
#define PF_INET6	AF_INET6

#define	FALSE	0
#define TRUE	1

#ifndef INET_ADDRSTRLEN
# define INET_ADDRSTRLEN        16
#endif /* INET_ADDRSTRLEN */

#ifndef INET6_ADDRSTRLEN
# define INET6_ADDRSTRLEN       46
#endif /* INET6_ADDRSTRLEN */

#include <stdio.h>

void PrintSocketAddress(const struct sockaddr *address, FILE *stream) {
	// Test for address and stream
	if (address == NULL || stream == NULL)
		return;

	void *numericAddress; // Pointer to binary address
	
	// Buffer to contain result (IPv6 sufficient to hold IPv4)
	char addrBuffer[INET6_ADDRSTRLEN];
	in_port_t port; // Port to print

	// Set pointer to address based on address family
	switch (address->sa_family) {
		case AF_INET:
			numericAddress = &((struct sockaddr_in *) address)->sin_addr;
			port = ntohs(((struct sockaddr_in *) address)->sin_port);
			break;
		case AF_INET6:
			numericAddress = &((struct sockaddr_in6 *) address)->sin6_addr;
			port = ntohs(((struct sockaddr_in6 *) address)->sin6_port);

			break;
		default:
			fputs("[unknown type]", stream);
		
		// Unhandled type
		return;
	}

	// Convert binary to printable address
	if (inet_ntop(address->sa_family, numericAddress, addrBuffer, sizeof(addrBuffer)) == NULL) {
		fputs("[invalid address]", stream); // Unable to convert
	} else {
		fprintf(stream, "%s", addrBuffer);
		if (port != 0) {
			// Zero not valid in any socket addr
			fprintf(stream, "-%u", port);
		}
	}
}
