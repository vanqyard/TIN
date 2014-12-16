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
#include "destroy/destroy.h"

int main(int argc, char **argv) {
	if(argc <= 1) {
		printf("Wprowadź poprawnie parametry!\ndaemon | get | update | init\n");
		return 1;
	}

	if(!strcmp(argv[1], DAEMON)) {
		return daemonMain(argc, argv);
	}

	else if(!strcmp(argv[1], GET)) {
		return getMain(argc, argv);
	}

	else if(!strcmp(argv[1], UPDATE)) {
		return updateMain(argc, argv);
	}

	else if(!strcmp(argv[1], INIT)) {
		return initMain(argc, argv);
	}

	else if(!strcmp(argv[1], DESTROY)) {
		return destroyMain(argc, argv);
	}

	return 1;
}
