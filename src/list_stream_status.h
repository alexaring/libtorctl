/*
 * =====================================================================================
 *
 *       Filename:  list_stream_status.h
 *
 *    Description:  list_stream_status header file
 *
 *        Version:  1.0
 *        Created:  10/04/2010 11:30:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __LIST_STREAM_STATUS_H__
#define __LIST_STREAM_STATUS_H__

#include <stdlib.h>
#include <string.h>
#include "socket.h"

//See https://gitweb.torproject.org/tor.git/blob/HEAD:/doc/spec/control-spec.txt
typedef enum {
	NEW,
	NEWRESOLVE,
	REMAP,
	SENTCONNECT,
	SENTRESOLVE,
	SUCCEEDED,
	FAILED,
	CLOSED,
	DETACHED
} E_STREAM_STATUS;

//struct for StreamID SP StreamStatus SP CircID SP Target
struct StreamStatusItem;
struct StreamStatusItem {
	int stream_id;
	E_STREAM_STATUS status;
	int circuit_id;
	char* target_ip;
	char* target_port;
};

struct LiStreamStatus;
struct LiStreamStatus {
	struct StreamStatusItem* s;
	struct LiStreamStatus* next;
};

static int init_stream_status(struct StreamStatusItem** item,
		int stream_id,
		E_STREAM_STATUS status,
		int circuit_id,
		char* target_ip,
		char* target_port);

static int free_stream_status(struct StreamStatusItem** item);

static int add_to_list(struct LiStreamStatus* li,
		int stream_id,
		E_STREAM_STATUS status,
		int circuit_id,
		char* target_ip,
		char* target_port);

int list_stream_status_init(struct LiStreamStatus** item);

int list_stream_status_free(struct LiStreamStatus** item);

#endif

