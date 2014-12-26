#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// "/home/vanqyard/Desktop/GTA2.exe"

/**
 * @author vanqyard
 * 
 * @brief returns file size
 * @param just file name
 * @return size of file
 */ 
long getFileSize(const char* filename) {
	struct stat fstatBuffer;
	stat(filename, &fstatBuffer);
	//printf("%d\n", fstatBuffer.st_size);

	return fstatBuffer.st_size;
}

/**
 * @author vanqyard
 * 
 * @param from
 * @param to
 * @brief returns bytes between param 'from' to param 'to'
 * @param buffer for data
 */ 
long getDataPacket(long from, long to, char* buffer) {
	
}
