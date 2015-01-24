/*
 * lib.c
 *
 *  Created on: 7 gru 2014
 *      Author: kamil
 */

#include <sys/stat.h>
#include <string.h>
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

void copyFile(const char *name) {
	FILE *input, *output;
	char buffer;
	char new_name[MAX_LENGTH];

	strcpy(new_name, PREFIX);
	strcat(new_name, name);

	input = fopen(name, "r");
	output = fopen(new_name, "w");

	while(fread(&buffer, 1, 1, input) == 1) {
		fwrite(&buffer, 1, 1, output);
	}

	fclose(output);
	fclose(input);
}

void deleteFile(const char *name) {
	char new_name[MAX_LENGTH];

	strcpy(new_name, PREFIX);
	strcat(new_name, name);

	remove(new_name);
}

int removeAll() {
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(".")) == NULL) {
		return 1;
	}

	while ((ent = readdir(dir)) != NULL) {
		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
			continue;
		}

		if (!strncmp(ent->d_name, PREFIX, strlen(PREFIX))) {
			remove(ent->d_name);
		}
	}
	closedir(dir);

	return 0;
}
