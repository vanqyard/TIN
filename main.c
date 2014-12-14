/*
 * main.c
 *
 *  Created on: 7 gru 2014
 *      Author: kamil
 */

#include <string.h>
#include "lib.h"
#include "daemon/daemon.h"
#include "get/get.h"
#include "update/update.h"
#include "init/init.h"

int main(int argc, char **argv) {
	if(argc <= 1) {
		printf("Wprowadź poprawnie parametry!\ndaemon | get | update | init\n");
		return 1;
	}

	if(strcmp(argv[1], DAEMON) == 0) {
		return daemonMain(argc, argv);
	}

	else if(strcmp(argv[1], GET) == 0) {
		return getMain(argc, argv);
	}

	else if(strcmp(argv[1], UPDATE) == 0) {
		return updateMain(argc, argv);
	}

	else if(strcmp(argv[1], INIT) == 0) {
		return initMain(argc, argv);
	}

	return 1;
}
