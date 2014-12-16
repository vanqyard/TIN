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

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"
#define DESTROY	"destroy"

#define CONFIG_NAME		".tin"
#define TEMP_NAME		".temp_tin"
#define SEPARATOR		'\t'
#define EXISTS_FLAG		"EXISTS"
#define DELETED_FLAG	"DELETED"
#define MAX_LENGTH		255
#define PERIOD			2
#define PREFIX			".tin."

int fileExists(const char *name);
void copyFile(const char *name);
void deleteFile(const char *name);

#endif /* LIB_H_ */
