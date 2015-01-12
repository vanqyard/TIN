/*
 * daemon.h
 *
 *  Created on: 8 gru 2014
 *      Author: kamil
 */

#ifndef DAEMON_H_
#define DAEMON_H_

int daemonMain(int argc, char **argv);
void doListen();
void doSend();

#endif /* DAEMON_H_ */
