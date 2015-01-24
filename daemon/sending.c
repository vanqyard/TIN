#include "daemon.h"

int sendConfFileData(struct MSG *msg1, int sock, struct sockaddr_in *address, socklen_t length) {
	unsigned int size;
	FILE *file;
	struct MSG *msg2;

	if((file = fopen(CONFIG_NAME, "r")) == NULL) {
		return -1;
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	if(size > CONF_FILE_LENGTH) {
		return -1;
	}

	fseek(file, 0, SEEK_SET);
	msg2 = malloc(sizeof(struct MSG));
	if(fread(msg2->content.cfd.data, 1, size, file) != size) {
		return -1;
	}
	msg2->flag = CFD;
	msg2->content.cfd.size = size;

	address->sin_port = htons(GET_PORT);
	return sendto(sock, msg2, sizeof(struct MSG), 0, (struct sockaddr *)address, length);
}

int sendPortFileData(struct MSG *msg1, int sock, struct sockaddr_in *address, socklen_t length) {
	unsigned int size, position;
	FILE *file;
	char *data;
	struct MSG *msg2;

	if((file = fopen(msg1->content.pfr.name, "r")) == NULL) {
		return -1;
	}

	fseek(file, 0, SEEK_END);
	position = msg1->content.pfr.number * PORT_FILE_LENGTH;
	size = max(PORT_FILE_LENGTH, ftell(file) - position);
	data = malloc(size);

	fseek(file, position, SEEK_SET);
	if(fread(data, 1, size, file) != size) {
		return -1;
	}

	msg2 = malloc(sizeof(struct MSG));
	msg2->flag = PFD;
	memcpy(msg2->content.pfd.name, msg1->content.pfd.name, strlen(msg1->content.pfd.name));
	msg2->content.pfd.number = msg1->content.pfd.number;
	msg2->content.pfd.size = size;
	memcpy(msg2->content.pfd.data, data, size);

	return sendto(sock, msg2, sizeof(struct MSG), 0, (struct sockaddr *)address, length);
}
