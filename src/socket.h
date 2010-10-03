/*
 * =====================================================================================
 *
 *       Filename:  socket.h
 *
 *    Description:  Socket Header file
 *
 *        Version:  1.0
 *        Created:  10/02/2010 07:57:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __TORSOCKET_H__
#define __TORSOCKET_H__

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>

int open_socket();
int close_socket();
int send_request(char* cmd);
int recv_request(char** result);

#endif

