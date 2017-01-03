/*
 * CreateTCPServerSocket.c
 *
 *  Created on: 29-dec.-2016
 *      Author: wdedul01
 */
#include "socket.h"
#define MAXPENDING 5

SOCKET CreateTCPServerSocket( int port ) {

	if( sockInit() < 0 ) {
		return -1;
	}

	SOCKET sock;

	/* Create socket for incoming connections */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		return -1;
	}

	/* bind the socket */
	if( sockBind(sock, port) < 0 ) {
		return -1;
	}

	/* Mark the socket so it will listen for incoming connections */
	if( listen(sock, MAXPENDING) < 0 ) {
		return -1;
	}

	return sock;
}
