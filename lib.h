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
#include <sys/stat.h>

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"

#define CONFIG_NAME ".tin"

struct config {
	char *name;
	long modify;
	long size;
};

struct list {
	struct config *config;
	struct list *next;
};

int fileExists(const char *name);
void openConfig();

#endif /* LIB_H_ */
