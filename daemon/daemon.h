/*
 * daemon.h
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../lib.h"

int daemonMain(int argc, char **argv);
int doListen(int sock, struct sockaddr_in *address, socklen_t length);
int sendConfFileData(MSG_CFR *confFileRequest, int sock, struct sockaddr_in *address, socklen_t length);
int sendPortFileData(MSG_PFR *portFileRequest, int sock, struct sockaddr_in *address, socklen_t length);

#endif /* DAEMON_H_ */
