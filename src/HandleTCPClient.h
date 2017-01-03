/*
 * HandleTCPClient.h
 *
 *  Created on: 3-jan.-2017
 *      Author: wdedul01
 */

#ifndef HANDLETCPCLIENT_H_
#define HANDLETCPCLIENT_H_

#include "socket.h"

typedef struct {
	int payloadSize;
	SOCKET clientSocket;
} payloadSocketRequest;

void HandleTCPClient(SOCKET socket);
int readRequestPayloadSize(SOCKET socket);
void handlePayload(payloadSocketRequest payloadRequest);

#endif /* HANDLETCPCLIENT_H_ */
