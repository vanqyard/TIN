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
#include <time.h>

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"

#define CONFIG_NAME ".tin"
#define CONFIG_TEMP_NAME ".temp_tin"
#define SEPARATOR '\t'
#define EXISTS_FLAG "EXISTS"
#define DELETED_FLAG "DELETED"
#define MAX_LENGTH 255

int fileExists(const char *name);

#endif /* LIB_H_ */
