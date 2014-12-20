struct UDPSocketForFileFragment {
	/**
	 * Pointer to memory where bytes from file are located.
	 * They are only pure bytes - we do not interpret them at this level
	 */ 
	char* cleanBytes;
	
	/**
	 * Number of bytes to send
	 * 
	 */ 
	int numOfBytes;
	
	/**
	 * Socket which handles sending bytes
	 * 
	 */ 
	int sock;
}
