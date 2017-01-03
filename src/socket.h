/*
 * socket.h
 *
 *  Created on: 3-jan.-2017
 *      Author: wdedul01
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

int sockInit(void);
int sockQuit(void);
int sockClose(SOCKET sock);
int sockBind(SOCKET sock, int port);

#endif /* SOCKET_H_ */
