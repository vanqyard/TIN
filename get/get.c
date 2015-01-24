/*
 * get.c
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#include "get.h"

int getMain(int argc, char **argv) {
	struct MSG *msg;
	struct NODE *root;

	msg = malloc(sizeof(struct MSG));
	msg->flag = CFR;
	sendToBroadcast(msg);

	receiveNodes(&root);

	return 0;
}
