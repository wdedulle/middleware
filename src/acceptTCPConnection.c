/*
 * acceptTCPConnection.c
 *
 *  Created on: 5-jan.-2017
 *      Author: wdedul01
 */
#include "acceptTCPConnection.h"

SOCKET acceptTCPConnection( SOCKET serverSocket ){
	SOCKET clientSocket = accept(serverSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		return -1;
	}

	return clientSocket;
}
