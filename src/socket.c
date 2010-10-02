/*
 * =====================================================================================
 *
 *       Filename:  socket.c
 *
 *    Description:  Socket c file
 *
 *        Version:  1.0
 *        Created:  10/02/2010 07:58:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "socket.h"

static int s;

int open_socket() {
	struct sockaddr_in remote;
	int err;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s<0) {
		return -1;
	}
	remote.sin_family = AF_INET;
	remote.sin_port = htons(9051);
	remote.sin_addr.s_addr = inet_addr("127.0.0.1");
	err = connect(s, (struct sockaddr*)&remote, sizeof(struct sockaddr_in));
    if (err<0) {
		return -1;
    }
	return 0;
}

int send_request(char* cmd) {
	return 0;
}

char* send_request() {
	return NULL;
}

int close_socket() {
	int err;
	err = close(s);
	if (err<0) {
		return -1;
	}
	return 0;
}

