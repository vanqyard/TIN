/*
 * update.h
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#ifndef UPDATE_H_
#define UPDATE_H_

#include "../lib.h"

int updateMain(int argc, char **argv);
void updateFile(const char *name);
void copyFile(const char *name);
void deleteFile(const char *name);

#endif /* UPDATE_H_ */
