/*
 * init.c
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#include "../lib.h"
#include "init.h"

int init(int argc, char **argv) {
	char c;
	FILE *f;

	if(fileExists(CONFIG_NAME)) {
		printf("Plik konfiguracyjny już istnieje.\nCzy chcesz stworzyć go ponownie?\n(T - tak, inny znak - zakończ)\n");
		scanf("%c", &c);
		if(c != 'T') {
			return 1;
		}
	}

	if((f = fopen(CONFIG_NAME, "w+")) == NULL) {
		printf("Wystąpił problem ze stworzeniem pliku!\n");
		return 1;
	}
	fclose(f);

	return 0;
}
