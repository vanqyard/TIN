/*
 * main.c
 *
 *  Created on: 7 gru 2014
 *      Author: kamil
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "daemon.h"
#include "get.h"
#include "update.h"
#include "init.h"

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"

int main(int argc, char **argv) {
	if(argc < 2) {
		return 1;
	}

	if(strcmp(argv[1], DAEMON) == 0) {
		return daemon(argc, argv);
	}

	else if(strcmp(argv[1], GET) == 0) {
		return get(argc, argv);
	}

	else if(strcmp(argv[1], UPDATE) == 0) {
		return update(argc, argv);
	}

	else if(strcmp(argv[1], INIT) == 0) {
		return init(argc, argv);
	}

	return 1;
}
