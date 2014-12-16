/*
 * destroy.c
 *
 *  Created on: 16 gru 2014
 *      Author: kamil
 */

#include <dirent.h>
#include <string.h>
#include "../lib.h"
#include "destroy.h"

int destroyMain(int argc, char **argv) {
	char c;
	DIR *dir;
	struct dirent *ent;

	if(!fileExists(CONFIG_NAME)) {
		printf("Nie znalezniono repozytorium!\n");
		return 1;
	}

	printf("Jestś pewien, że chcesz usunąć repozytorium?\n(T - tak, inny znak - zakończ)\n");
	scanf("%c", &c);
	if (c != 'T') {
		return 0;
	}

	remove(CONFIG_NAME);

	if ((dir = opendir(".")) == NULL) {
		printf("Wystąpił problem z oczytem katalogu!\n");
		return 1;
	}

	while((ent = readdir(dir)) != NULL) {
		if(!strcmp(ent->d_name, ".")
		|| !strcmp(ent->d_name, "..")) {
			continue;
		}

		if(!strncmp(ent->d_name, PREFIX, strlen(PREFIX))) {
			remove(ent->d_name);
		}
	}

	closedir(dir);
	printf("Pomyślnie usunięto repozytorium.\n");

	return 0;
}
