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

#define MAX_SIZE 5242880
#define BUFFER_SIZE 5242880

static int s;

int open_socket(char* server, unsigned short port) {
	struct sockaddr_in remote;
	size_t strlength;
	int err;
	
	//Avoid Bufferoverflow
	strlength = strlen(server);
	if (strlength>16) {
		return -1;
	}

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s<0) {
		return -1;
	}

	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	remote.sin_addr.s_addr = inet_addr(server);
	
	err = connect(s, (struct sockaddr*)&remote, sizeof(struct sockaddr_in));
    if (err<0) {
		return -1;
    }
	
	return 0;
}

int send_request(char* cmd) {
	int err;
	char* send_cmd;
	size_t strlength;
	strlength = strlen(cmd); 
	send_cmd = (char*)malloc(strlength+2);
	memset(send_cmd, 0, strlength+2);
	strcpy(send_cmd, cmd);
	//Each command must be end with CRLF
	send_cmd[strlength] = '\r';
	send_cmd[strlength+1] = '\n';
	err = send(s, (void*)send_cmd, strlength+2, 0);
	if (err<0) {
		free((void*)send_cmd);
		return -1;
	}
	free((void*)send_cmd);
	return 0;
}

int recv_request(char** result) {
	size_t size;
	int i, err, is_end;
	is_end = 0;
	size = BUFFER_SIZE;
	*result = (char*)malloc(size);
	if (!*result || size>MAX_SIZE) {
		return -1;
	}
	memset(*result, 0, size);
	if (!*result) {
		return -1;
	}
	for ( i=0;!is_end;i++ ) {
		err = recv(s, (void*)((char*)(*result)+i), 1, 0);
		if (err<0) {
			return -1;
		}
		if (((i+1)%BUFFER_SIZE) == 0) {
			size += BUFFER_SIZE;
			*result = (char*)realloc((void*)(*result), size);
			if (!*result || size>MAX_SIZE) {
				return -1;
			}
		}
		//Match on 250-...CRLF
		if ((i > 3) 
				&& ((*result)[0] == '2') 
				&& ((*result)[1] == '5') 
				&& ((*result)[2] == '0') 
				&& ((*result)[3] == '-') 
				&& ((*result)[i-1] == '\r') 
				&& ((*result)[i] == '\n')) {
			is_end = 1;
			//Check if reply fits into result
			if (i+8 > size) {
				size += BUFFER_SIZE;
				*result = (char*)realloc((void*)(*result), size);
				if (!*result || size>MAX_SIZE) {
					return -1;
				}
			}
			err = recv(s, (void*)(((char*)(*result))+i+1), 8, 0);
			if (err<0) {
				return -1;
			}
			i+=8;
			is_end = 1;
		}
		//Match on 250 ...CRLF
		if ((i > 3) 
				&& ((*result)[0] == '2') 
				&& ((*result)[1] == '5') 
				&& ((*result)[2] == '0') 
				&& ((*result)[3] == ' ') 
				&& ((*result)[i-1] == '\r') 
				&& ((*result)[i] == '\n')) {
			is_end = 1;
		}
		// Match on 250+... with emsequence CRLF.CRLF
		if ((i > 4) 
				&& ((*result)[0] == '2') 
				&& ((*result)[1] == '5') 
				&& ((*result)[2] == '0') 
				&& ((*result)[3] == '+') 
				&& ((*result)[i-4] == '\r') 
				&& ((*result)[i-3] == '\n') 
				&& ((*result)[i-2] == '.') 
				&& ((*result)[i-1] == '\r') 
				&& ((*result)[i] == '\n')) {
			//Check if reply fits into result
			if (i+8 > size) {
				size += BUFFER_SIZE;
				*result = (char*)realloc((void*)(*result), size);
				if (!*result || size>MAX_SIZE) {
					return -1;
				}
			}
			err = recv(s, (void*)((char*)(*result)+i+1), 8, 0);
			if (err<0) {
				return -1;
			}
			i+=8;
			is_end = 1;
		}
		//Match on 3DIGITS ... CRLF
		if ((i > 2) 
				&& !(((*result)[0] == '2') 
					&& ((*result)[1] == '5') 
					&& ((*result)[2] == '0')) 
				&& ((*result)[i-1] == '\r') 
				&& ((*result)[i] == '\n')) {
			is_end = 1;
		}
	}
	return 0;
}

int close_socket() {
	int err;
	err = close(s);
	if (err<0) {
		return -1;
	}
	return 0;
}

