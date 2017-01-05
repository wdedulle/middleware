/*
 ============================================================================
 Name        : c_practice.c
 Author      : Dulle Education
 Version     :
 Copyright   : Your copyright notice
 Description : Practice C, Ansi-style
 Windows
 Using the standard winsock
 -lws2_32
 -lpthread
 using libxml from http://xmlsoft.org/sources/win32/64bit/
 -I"C:\Data\lib\libxml\include"
 "C:\Data\lib\iconv\bin\libxml2-2.dll"

 Unix
 gcc `xml2-config --cflags --libs` -o c_practice c_practice.c -lsocket

 ============================================================================
 */
#pragma pack(1)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "createTCPServerSocket.h"
#include "acceptTCPConnection.h"
#include "handleTCPClient.h"
#include "socket.h"

void *threadMain(void *arg);

/* Structure of arguments to pass to client thread */
typedef struct {
	SOCKET clientSock;
} ThreadArgs;

int main(void) {
	int serverSocket;
	int clientSocket;
	int serverPort = 8888;
	pthread_t threadID;
	ThreadArgs *threadArgs;

	printf("starting socket server...\n");
	serverSocket = createTCPServerSocket(serverPort);
	if (serverSocket < 0) {
		printf("unable to create socker server...\n");
		return EXIT_FAILURE;
	}
	printf("socket server started...\n");

	while (1) {
		clientSocket = acceptTCPConnection(serverSocket);
		if (clientSocket < 0) {
			return EXIT_FAILURE;
		}
		printf("client accepted...\n");

		/* Create separate memory for client argument */
		threadArgs = (ThreadArgs *) malloc(sizeof(ThreadArgs));
		if (threadArgs == NULL) {
			return EXIT_FAILURE;
		}
		threadArgs->clientSock = clientSocket;
		/* Create client handle thread */
		if (pthread_create(&threadID, NULL, threadMain, (void *) threadArgs)
				!= 0) {
			return EXIT_FAILURE;
		}

		printf("with thread %ld\n", (long int) threadID);
	}
	sockClose(serverSocket);
	printf("Socket closed.\n");
	sockQuit();
	printf("Socket quit.\n");
	return EXIT_SUCCESS;
}

void *threadMain(void *threadArgs) {
	pthread_detach(pthread_self());

	handleTCPClient(((ThreadArgs *) threadArgs)->clientSock);
	free(threadArgs);

	return (NULL);
}
