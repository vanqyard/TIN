/*

 * update.c
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include "../lib.h"
#include "update.h"

int updateMain(int argc, char **argv) {
	int i;
	DIR *dir;
	struct dirent *ent;
	FILE *config;
	char temp_name[MAX_LENGTH], temp[MAX_LENGTH];

	if(!fileExists(CONFIG_NAME)) {
		printf("Nie znaleziono pliku konfiguracyjnego!\n");
		return 1;
	}

	if(argc == 2) {
		if((dir = opendir(".")) == NULL) {
			printf("Wystąpił problem z oczytem katalogu!\n");
			return 1;
		}

		while((ent = readdir(dir)) != NULL) {
			if(ent->d_name[0] == '.') {
				continue;
			}

			updateFile(ent->d_name);
		}

		closedir(dir);

		if((config = fopen(CONFIG_NAME, "r")) == NULL) {
			return 1;
		}

		while(fscanf(config,"%[^\t]\t%s\t%s\t%s\n", temp_name, temp, temp, temp) != EOF) {
			updateFile(temp_name);
		}

		fclose(config);
	}
	else {
		for(i=2; i<argc; ++i) {
			updateFile(argv[i]);
		}
	}

	return 0;
}

void updateFile(const char *name) {
	struct stat s;
	char temp_name[MAX_LENGTH], temp_flag[MAX_LENGTH];
	long temp_date, temp_size;
	FILE *config, *config_temp;
	int exists = 0, modified = 0;

	if((config = fopen(CONFIG_NAME, "r")) == NULL
	|| (config_temp = fopen(CONFIG_TEMP_NAME, "w")) == NULL) {
		return;
	}

	if((stat(name, &s) == 0) && (s.st_mode & S_IFREG)) {
		exists = 1;
	}

	while(fscanf(config, "%[^\t]\t%ld\t%ld\t%s\n", temp_name, &temp_date, &temp_size, temp_flag) != EOF) {
		if(!exists) {
			if(!strcmp(name, temp_name) && strcmp(DELETED_FLAG, temp_flag)) {
				fprintf(config_temp, "%s\t%ld\t%ld\t%s\n", temp_name, time(NULL), temp_size, DELETED_FLAG);
				printf("Usunięto istniejący plik: %s\n", name);
				deleteFile(name);
			}
			else {
				fprintf(config_temp, "%s\t%ld\t%ld\t%s\n", temp_name, temp_date, temp_size, temp_flag);
			}
		}
		else {
			if(!strcmp(name, temp_name)) {
				fprintf(config_temp, "%s\t%ld\t%ld\t%s\n", temp_name, s.st_mtime, temp_size, EXISTS_FLAG);
				modified = 1;
				if(temp_date != s.st_mtime) {
					printf("Zmodyfikowano istniejący plik: %s\n", name);
					copyFile(name);
				}
			}
			else {
				fprintf(config_temp, "%s\t%ld\t%ld\t%s\n", temp_name, temp_date, temp_size, temp_flag);
			}
		}
	}
	if(exists && !modified) {
		fprintf(config_temp, "%s\t%ld\t%ld\t%s\n", name, s.st_mtime, s.st_size, EXISTS_FLAG);
		printf("Dodano nowy plik: %s\n", name);
		copyFile(name);
	}

	fclose(config_temp);
	fclose(config);

	remove(CONFIG_NAME);
	rename(CONFIG_TEMP_NAME, CONFIG_NAME);
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
