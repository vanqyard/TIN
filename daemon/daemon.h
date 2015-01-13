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

int daemonMain(int argc, char **argv);
int doListen(int sock, struct sockaddr* pcliaddr, socklen_t clilen);
int doSend();

#endif /* DAEMON_H_ */
