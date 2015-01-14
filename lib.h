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

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"
#define DESTROY	"destroy"

#define LOCAL_IP		"127.0.0.1"
#define BROADCAST_IP	"255.255.255.255"
#define DAEMON_PORT		2000
#define GET_PORT		2001

#define CONFIG_NAME		".tin"
#define TEMP_NAME		".temp_tin"
#define SEPARATOR		'\t'
#define EXISTS_FLAG		"EXISTS"
#define DELETED_FLAG	"DELETED"
#define MAX_LENGTH		255
#define PREFIX			".tin."

#define FLAG_CFR	0
#define FLAG_CFD	1
#define FLAG_PFR	2
#define FLAG_PFD	3

typedef struct MSG {
	char flag;
	char data[511];
} MSG;

typedef struct MSG_CFR {
	char flag;
	char data[511];
} MSG_CFR;

typedef struct MSG_CFD {
	char flag;
	unsigned int size;
	char data[507];
} MSG_CFD;

typedef struct MSG_PFR {
	char flag;
	char name[64];
	unsigned int number;
	char data[443];
} MSG_PFR;

typedef struct MSG_PFD {
	char flag;
	char name[64];
	unsigned int number;
	unsigned int size;
	char data[439];
} MSG_PFD;

int fileExists(const char *name);
void copyFile(const char *name);
void deleteFile(const char *name);

#endif /* LIB_H_ */
