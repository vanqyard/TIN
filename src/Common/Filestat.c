#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// "/home/vanqyard/Desktop/GTA2.exe"

long getFileSize(const char* filename) {
	struct stat fstatBuffer;
	stat(filename, &fstatBuffer);
	//printf("%d\n", fstatBuffer.st_size);

	return fstatBuffer.st_size;
}
