/*
 * get.h
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#ifndef GET_H_
#define GET_H_

#include "../lib.h"

int getMain(int argc, char **argv);
int sendToBroadcast(struct MSG *msg);
int receiveNodes(struct NODE **root);

#endif /* GET_H_ */
