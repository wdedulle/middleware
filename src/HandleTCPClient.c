/*
 * HandleTCPClient.c
 *
 *  Created on: 3-jan.-2017
 *      Author: wdedul01
 */
#include <libxml/parser.h>
#include <libxml/xinclude.h>
#include "socket.h"
#include "xml.h"
#include "HandleTCPClient.h"
#define RCVBUFSIZE 32

void HandleTCPClient(SOCKET socket) {
	int payloadSize;
	while ((payloadSize = readRequestPayloadSize(socket)) > 0) {
		payloadSocketRequest payloadRequest;
		payloadRequest.clientSocket = socket;
		payloadRequest.payloadSize = payloadSize;

		handlePayload(payloadRequest);
	}
	puts("client closed");
	sockClose(socket);

	/*
	 char echoBuffer[RCVBUFSIZE];
	 int recvMsgSize;

	 // Buffer for echo string
	 // Size of received message
	 // Receive message from client
	 if ((recvMsgSize = recv(socket, echoBuffer, RCVBUFSIZE, 0)) < 0) {
	 return;
	 }

	 // Send received string and receive again until end of transmission
	 // zero indicates end of transmission
	 while (recvMsgSize > 0) {
	 // Echo message back to client
	 if (send(socket, echoBuffer, recvMsgSize, 0) != recvMsgSize) {
	 return;
	 }

	 // See if there is more data to receive
	 if ((recvMsgSize = recv(socket, echoBuffer, RCVBUFSIZE, 0)) < 0) {
	 return;
	 }
	 }

	 close(socket); // Close client socket
	 */
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

	int recv_size;

	char clientPayload[payloadRequest.payloadSize];
	recv_size = recv(payloadRequest.clientSocket, clientPayload, payloadRequest.payloadSize, 0);
	if (recv_size == SOCKET_ERROR) {
		puts("recv clientPayload failed");
		return;
	}

	if( recv_size < payloadRequest.payloadSize )  {
		puts( clientPayload );
		return;
	}

	//Add a NULL terminating character to make it a proper string before printing
	clientPayload[recv_size] = '\0';

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
