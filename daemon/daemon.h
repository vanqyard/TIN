/*
 * daemon.h
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include "../lib.h"

int daemonMain(int argc, char **argv);
int doListen();
int sendConfFileData(struct MSG *msg1, int sock, struct sockaddr_in *address, socklen_t length);
int sendPortFileData(struct MSG *msg1, int sock, struct sockaddr_in *address, socklen_t length);

#endif /* DAEMON_H_ */
