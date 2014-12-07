#include <sys/stat.h>

int UDPSendFile(const struct sockaddr *address, FILE *fdesc) {
	struct stat st;
	
	stat(filename, &st);
	size = st.st_size;
	
	
	
	
	
	
}
