/*
 ============================================================================
 Name        : c_practice.c
 Author      : Dulle Education
 Version     :
 Copyright   : Your copyright notice
 Description : Practice C, Ansi-style
 Windows
 -lws2_32
 -I"C:\Data\lib\libxml\include"
 "C:\Data\lib\iconv\bin\libxml2-2.dll"

 Unix
gcc `xml2-config --cflags --libs` -o c_practice c_practice.c -lsocket

 ============================================================================
 */
#pragma pack(1)

#include "c_practice.h"

int main(void) {

	Individual person = { "test", "mij" };

	PartyType partyType;
	partyType.individual = &person;

	Party party;
	party.partyId = "ddddd";
	party.partyType = &partyType;

	printf("union size %d\n", (int) sizeof(PartyType));

	printf("First name:\t%s\nLast name:\t %s\n", person.first_name,
			person.last_name);

	printf("Party First name:\t%s\nParty Last name:\t %s\n",
			party.partyType->individual->first_name,
			party.partyType->individual->last_name);

	bindSocket();

	return EXIT_SUCCESS;
}

void bindSocket() {

	if (sockInit() == 0) {
		SOCKET s;
		//Create a socket
		if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
			printf("Could not create socket : %d", WSAGetLastError());
		}

		sockBind(s);

		listen(s, 3);

		struct sockaddr_in client;
		int c = sizeof(struct sockaddr_in);
		SOCKET new_socket;

		while ((new_socket = accept(s, (struct sockaddr *) &client, &c))
				!= INVALID_SOCKET ) {
			int recv_size;
			char clientRequest[SO_MAX_MSG_SIZE];
			//Receive a reply from the server
			if ((recv_size = recv(new_socket, clientRequest, SO_MAX_MSG_SIZE, 0))
					== SOCKET_ERROR) {
				puts("recv failed");
			}

			//Add a NULL terminating character to make it a proper string before printing
			clientRequest[recv_size] = '\0';

			puts(clientRequest);
			char * requestPayload;
			char *message;
			if(( requestPayload = strstr(clientRequest, "\r\n\r\n")) != NULL) {
				if( xmlProcess(requestPayload) == 0) {
					message = "HTTP/1.x 200 OK\r\nContent-Length: 19\r\n\r\n<xml>received</xml>";
				} else {
					message = "HTTP/1.x 200 OK\r\nContent-type: application/xml\r\nContent-Length: 26\r\n\r\n<xml>failed to parse</xml>";
				}
			} else {
				message = "HTTP/1.x 200 OK\r\nContent-type: application/xml\r\nContent-Length: 13\r\n\r\n<xml>no</xml>";
			}
			puts(message);

			send(new_socket , message , (int)strlen(message) , 0);

			sockClose(new_socket);
		}

		sockClose(s);
		printf("Socket closed.\n");
		sockQuit();
		printf("Socket quit.\n");
	}
}
