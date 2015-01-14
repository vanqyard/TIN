#include "daemon.h"

int sendConfFileData(MSG_CFR *confFileRequest, int sock, struct sockaddr_in *address, socklen_t length) {
	unsigned int size;
	int result;
	FILE *file;
	char *data;
	MSG_CFD confFileData;

	if((file = fopen(CONFIG_NAME, "r")) == NULL) {
		return -1;
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	if(size > CONF_FILE_LENGTH) {
		return -1;
	}
	data = malloc(size);

	fseek(file, 0, SEEK_SET);
	if(fread(data, 1, size, file) != size) {
		return -1;
	}

	confFileData.flag = FLAG_CFD;
	confFileData.size = size;
	memcpy(confFileData.data, &data, size);

	result = sendto(sock, &confFileData, sizeof(MSG_CFD), 0, (struct sockaddr *)address, length);

	return result;
}

int sendPortFileData(MSG_PFR *portFileRequest, int sock, struct sockaddr_in *address, socklen_t length) {
	unsigned int size, position;
	int result;
	FILE *file;
	char *data;
	MSG_PFD portFileData;

	if((file = fopen(portFileRequest->name, "r")) == NULL) {
		return -1;
	}

	fseek(file, 0, SEEK_END);
	position = portFileRequest->number*PORT_FILE_LENGTH;
	size = max(PORT_FILE_LENGTH, ftell(file) - position);
	data = malloc(size);

	fseek(file, position, SEEK_SET);
	if(fread(data, 1, size, file) != size) {
		return -1;
	}

	portFileData.flag = FLAG_PFD;
	memcpy(portFileData.name, portFileRequest->name, strlen(portFileRequest->name));
	portFileData.number = portFileRequest->number;
	portFileData.size = size;
	memcpy(portFileData.data, data, size);

	result = sendto(sock, &portFileData, sizeof(portFileData), 0, (struct sockaddr *)address, length);

	return result;
}
