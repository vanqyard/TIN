/*
 * lib.h
 *
 *  Created on: 7 gru 2014
 *      Author: kamil
 */

#ifndef LIB_H_
#define LIB_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <netdb.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define max(a,b) (((a)>(b))?(a):(b))

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"
#define DESTROY	"destroy"

#define BROADCAST_IP	"192.168.56.255"
#define DAEMON_PORT		2000
#define GET_PORT		2001

#define CONFIG_NAME			".tin"
#define TEMP_NAME			".temp_tin"
#define PREFIX				".tin."
#define SEPARATOR			'\t'
#define EXISTS_FLAG			"EXISTS"
#define DELETED_FLAG		"DELETED"
#define MAX_LENGTH			255
#define NAME_LENGTH			64
#define CONF_FILE_LENGTH	400
#define PORT_FILE_LENGTH	400

#define CFR	0
#define CFD	1
#define PFR	2
#define PFD	3

struct MSG {
	char flag;
	union {
		struct {} cfr;

		struct {
			unsigned int size;
			char data[CONF_FILE_LENGTH];
		} cfd;

		struct {
			unsigned int number;
			char name[NAME_LENGTH];
		} pfr;

		struct {
			unsigned int number;
			unsigned int size;
			char name[NAME_LENGTH];
			char data[PORT_FILE_LENGTH];
		} pfd;
	} content;
};

struct NODE {
	struct NODE *next;
	socklen_t length;
	struct sockaddr_in address;
	char data[CONF_FILE_LENGTH];
};

int fileExists(const char *name);
void copyFile(const char *name);
void deleteFile(const char *name);
int removeAll();

#endif /* LIB_H_ */
