/*
 * =====================================================================================
 *
 *       Filename:  list_stream_status.c
 *
 *    Description:  List stream status c file
 *
 *        Version:  1.0
 *        Created:  10/04/2010 11:30:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "list_stream_status.h"

static int init_stream_status(StreamStatusItem* item,
		int stream_id,
		E_STREAM_STATUS status,
		int circuit_id,
		char* target_ip,
		char* target_port) {
	return 0;
}


static int free_stream_status(StreamStatusItem* item) {
	return 0;
}

int list_init(StreamStatusItem** item) {
	*item = NULL;
	return 0;
}

int list_free(StreamStatusItem** item) {
	return 0;
}

