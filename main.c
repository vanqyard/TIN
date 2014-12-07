/*
 * main.c
 *
 *  Created on: 7 gru 2014
 *      Author: kamil
 */

#include <stdio.h>

#include "daemon.h"
#include "get.h"
#include "update.h"

#define DAEMON	"daemon"
#define GET 	"get"
#define UPDATE	"update"
#define INIT	"init"

int main(int argc, char **argv) {
	if(argc > 1) {
		return 1;
	}

	if(argv[1] == DAEMON) {
		return daemon(argc, argv);
	}

	else if(argv[1] == GET) {
		return get(argc, argv);
	}

	else if(argv[1] == UPDATE) {
		return update(argc, argv);
	}

	else if(argv[1] == INIT) {
		return init(argc, argv);
	}

	return 1;
}
