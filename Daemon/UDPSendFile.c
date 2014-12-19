#include <sys/stat.h>

int UDPSendFragmentedFile(const struct sockaddr *address, const char* filename) {
	FILE *filedesc;
	struct stat file_status;

	filedesc = fopen(filename, "r");
	filestat(filedesc, &file_status);
	size = file_status.st_size;
	
	struct* UDPSocketForFileFragment arg = 
		(struct* UDPSocketForFileFragment)malloc(
			sizeof(UDPSocketForFileFragment));

	arg.cleanBytes = ;
	arg.numOfBytes = ;
	arg.sock = ;
	
	// bedzie zwracalo wskaznik do wypelnionej funkcji coby puscic to na watek ???
	UDPSendFileFragment(arg);	
}

int UDPSendFileFragment(UDPSocketForFileFragment arg) {
	/**
	 * Counter that counts down to 0 which tells how many bytes we have 
	 * to send.
	 */ 
	int bytesCounter;
	
	/**
	 * The while loop which handles sending bytes to server.
	 */ 
	while(bytesCounter != 0) {
		
		
		
	}
}
