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
typedef struct {
	int stream_id;
	E_STREAM_STATUS status;
	int circuit_id;
	char* target_ip;
	char* target_port;
} StreamStatusItem;

struct Li;
typedef struct {
	StreamStatusItem s;
	struct Li* next;
} Li;

static int init_stream_status(StreamStatusItem* item,
		int stream_id,
		E_STREAM_STATUS status,
		int circuit_id,
		char* target_ip,
		char* target_port);

static int free_stream_status(StreamStatusItem* item);

int list_init(StreamStatusItem** item);

int list_free(StreamStatusItem** item);

#endif

