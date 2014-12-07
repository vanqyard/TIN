/*
 * lib.c
 *
 *  Created on: 7 gru 2014
 *      Author: kamil
 */

#include "lib.h"

int fileExists(const char *name) {
	struct stat s;
	int result = stat(CONFIG_NAME, &s);
	return result == 0;
}

void openConfig() {

}
