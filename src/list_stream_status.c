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

static int init_stream_status(struct StreamStatusItem** item,
		int stream_id,
		E_STREAM_STATUS status,
		int circuit_id,
		char* target_ip,
		char* target_port) {
	
	*item = malloc(sizeof(struct StreamStatusItem));
	
	if(!*item) {
		return -1;
	}
	
	(*item)->stream_id = stream_id;
	(*item)->status = status;
	(*item)->circuit_id = circuit_id;
	(*item)->target_ip = malloc(strlen(target_ip)+1);

	if ((*item)->target_ip == NULL) {
		return 0;
	}

	strcpy((*item)->target_ip, target_ip); 
	(*item)->target_port = malloc(strlen(target_port)+1);

	if ((*item)->target_port == NULL) {
		return 0;
	}

	strcpy((*item)->target_port, target_port); 

	return 0;
}


static int free_stream_status(struct StreamStatusItem** item) {
	free(*item);

	return 0;
}

int list_stream_status_init(struct LiStreamStatus** li) {
	char* recvstr;
	int err;

	err = send_request("getinfo stream-status");

	if (err<0) {
		printf("%s\n", "lalas");
		return -1;
	}

	err = recv_request(&recvstr);

	if (err<0) {
		printf("%s\n", "lala");
		free(recvstr);
		return -1;
	}

	printf("%s\n", recvstr);

	*li = NULL;

	return 0;
}

int list_stream_status_free(struct LiStreamStatus** li) {
	struct LiStreamStatus** tmp;
	int err;

	if ((*li) == NULL) {
		return 0;
	}

	err = free_stream_status(&((*li)->s));

	if (err<0) {
		return -1;
	}

	tmp = &((*li)->next);
	free(*li);
	err = list_stream_status_free(tmp);

	if (err<0) {
		return -1;
	}

	return 0;
}

static int add_to_list(struct LiStreamStatus* li,
		int stream_id,
		E_STREAM_STATUS status,
		int circuit_id,
		char* target_ip,
		char* target_port) {
	int err;

	if (li == NULL) {
		li = malloc(sizeof(struct LiStreamStatus));
		
		if (!li) {
			return -1;
		}

		err = init_stream_status(&(li->s),
				stream_id,
				status,
				circuit_id,
				target_ip,
				target_port);

		if(err<0) {
			return -1;
		}

		li->next = NULL;
		return 0;
	}

	if (li->next == NULL) {
		li->next = malloc(sizeof(struct LiStreamStatus));
		
		if (!li->next) {
			return -1;
		}

		err = init_stream_status(&(li->next->s),
				stream_id,
				status,
				circuit_id,
				target_ip,
				target_port);

		if(err<0) {
			return -1;
		}

		li->next->next = NULL;

		return 0;
	}

	err = add_to_list(li->next, stream_id, status, circuit_id, target_ip, target_port);

	if (err<0) {
		return -1;
	}

	return 0;
}

