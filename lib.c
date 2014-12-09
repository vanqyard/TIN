/*
 * lib.c
 *
 *  Created on: 7 gru 2014
 *      Author: kamil
 */

#include "lib.h"

int fileExists(const char *name) {
	struct stat s;
	if(stat(name, &s) == 0) {
		if(s.st_mode & S_IFREG) {
			return 1;
		}
	}
	return 0;
}
