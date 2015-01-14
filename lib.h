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

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"
#define DESTROY	"destroy"

#define LOCAL_IP		"10.0.2.15"
#define BROADCAST_IP	"10.0.2.255"
#define DAEMON_PORT		2000
#define GET_PORT		2001

#define CONFIG_NAME		".tin"
#define TEMP_NAME		".temp_tin"
#define SEPARATOR		'\t'
#define EXISTS_FLAG		"EXISTS"
#define DELETED_FLAG	"DELETED"
#define MAX_LENGTH		255
#define NAME_LENGTH		64
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
	char name[NAME_LENGTH];
	unsigned int number;
	char data[443];
} MSG_PFR;

typedef struct MSG_PFD {
	char flag;
	char name[NAME_LENGTH];
	unsigned int number;
	unsigned int size;
	char data[439];
} MSG_PFD;

#define CONF_FILE_LENGTH (sizeof(MSG_CFD) - sizeof(char) - sizeof(unsigned int))
#define PORT_FILE_LENGTH (sizeof(MSG_PFD) - sizeof(char) - NAME_LENGTH - sizeof(unsigned int) - sizeof(unsigned int))

int fileExists(const char *name);
void copyFile(const char *name);
void deleteFile(const char *name);

#endif /* LIB_H_ */
