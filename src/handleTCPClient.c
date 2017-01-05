/*
 * HandleTCPClient.c
 *
 *  Created on: 3-jan.-2017
 *      Author: wdedul01
 */
#include "handleTCPClient.h"

#include <libxml/parser.h>
#include <libxml/xinclude.h>
#include "socket.h"
#include "xml.h"
#define RCVBUFSIZE 32

void handleTCPClient(SOCKET socket) {
	int payloadSize;
	while ((payloadSize = readRequestPayloadSize(socket)) > 0) {
		payloadSocketRequest payloadRequest;
		payloadRequest.clientSocket = socket;
		payloadRequest.payloadSize = payloadSize;

		handlePayload(payloadRequest);
	}
	puts("client closed");
	sockClose(socket);
}


int readRequestPayloadSize(SOCKET socket) {

	int recv_size;
	char clientRequest[4];

	//Receive a reply from the server
	if ((recv_size = recv(socket, clientRequest, 4, 0)) == SOCKET_ERROR) {
		puts("recv clientRequest failed");
		return -1;
	}

	return atoi(clientRequest);

}

void handlePayload(payloadSocketRequest payloadRequest) {
	int received = 0;
	char clientPayload[payloadRequest.payloadSize];

	while( received < payloadRequest.payloadSize ) {
		int recv_size;
		recv_size = recv(payloadRequest.clientSocket, clientPayload+received, 1, 0);
		if (recv_size == SOCKET_ERROR) {
			puts("recv clientPayload failed");
			return;
		}

		received++;
	}

	if( received < payloadRequest.payloadSize )  {
		puts( clientPayload );
		return;
	}

	//Add a NULL terminating character to make it a proper string before printing
	clientPayload[received] = '\0';

	char * message;
	xmlProcess(clientPayload);

	char responseSize[4];
/*
	xmlError * error = xmlGetLastError();
	if (error) {
		sprintf(responseSize, "%.4d", (int) strlen(error->message) + 10);
		message = responseSize;
		send(payloadRequest.clientSocket, message, 4, 0);

		message = "<xml>";
		send(payloadRequest.clientSocket, message, (int) strlen(message), 0);
		message = error->message;
		send(payloadRequest.clientSocket, message, (int) strlen(message), 0);
		message = "</xml>";
		send(payloadRequest.clientSocket, message, (int) strlen(message), 0);

	} else {
	*/
		sprintf(responseSize, "%.4d", 19);
		message = responseSize;
		send(payloadRequest.clientSocket, message, 4, 0);

		message = "<xml>received</xml>";
		send(payloadRequest.clientSocket, message, (int) strlen(message), 0);
	//}

	return;
}
