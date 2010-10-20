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

static char* copy_sub_str_trimmed(char* str, char delimeter) {
	size_t i;
	char* erg;

	for (i=1;(str[i]!=delimeter);i++);
	
	erg = (char*)malloc(i+1);
	
	strncpy(erg, str, i);
	
	erg[i] = '\0';

	return erg;
}

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

	if (!(*item)->target_ip) {
		return 0;
	}

	strcpy((*item)->target_ip, target_ip); 
	(*item)->target_port = malloc(strlen(target_port)+1);

	if (!(*item)->target_port) {
		return 0;
	}

	strcpy((*item)->target_port, target_port); 

	return 0;
}


static int free_stream_status(struct StreamStatusItem** item) {
	if (!*item) {
		return -1;
	}

	free(*item);

	return 0;
}

int list_stream_status_init(struct LiStreamStatus** li) {
	char* recvstr, *tmp, *str;
	int err;
	E_RESPONSE_TYPE responsetype;
	struct StreamStatusItem item;

	err = send_request("getinfo stream-status");

	if (err<0) {
		return -1;
	}

	err = recv_request(&recvstr);

	if (err<0) {
		free(recvstr);
		return -1;
	}

	*li = NULL;

	responsetype = get_reply_type(recvstr);
	printf("%s\n", recvstr);

	switch (responsetype) {
		case RESPONSE_LINE:
			tmp = rindex(recvstr, '=')+1;

			str = copy_sub_str_trimmed(tmp, ' ');
			item.stream_id = strtol(str, NULL, 10);
			free(str);

			tmp = index(tmp, ' ')+1;
			str = copy_sub_str_trimmed(tmp, ' ');

			if (!strcmp(str, "NEW\0")) {
				item.status = NEW;
			}
			else if (!strcmp(str, "NEWRESOLVE\0")) {
				item.status = NEWRESOLVE;
			}
			else if (!strcmp(str, "REMAP\0")) {
				item.status = REMAP;
			}
			else if (!strcmp(str, "SENTCONNECT\0")) {
				item.status = SENTCONNECT;
			}
			else if (!strcmp(str, "SENTRESOLVE\0")) {
				item.status = SENTRESOLVE;
			}
			else if (!strcmp(str, "SUCCEEDED\0")) {
				item.status = SUCCEEDED;
			}
			else if (!strcmp(str, "FAILED\0")) {
				item.status = FAILED;
			}
			else if (!strcmp(str, "CLOSED\0")) {
				item.status = CLOSED;
			}
			else if (!strcmp(str, "DETACHED\0")) {
				item.status = DETACHED;
			}
			else {
				return -1;
			}

			free(str);

			tmp = index(tmp, ' ')+1;
			str = copy_sub_str_trimmed(tmp , ' ');
			item.circuit_id = strtol(str, NULL, 10);
			free(str);

			tmp = index(tmp, ' ')+1;
			str = copy_sub_str_trimmed(tmp, ':');
			item.target_ip = malloc(strlen(str)+1);	
			strcpy(item.target_ip, str);
			free(str);

			tmp = index(tmp, ':')+1;
			str = copy_sub_str_trimmed(tmp, '\n');
			item.target_port = malloc(strlen(str)+1);	
			strcpy(item.target_port, str);
			free(str);

			add_to_list(li, 
					item.stream_id,
					item.status,
					item.circuit_id,
					item.target_ip,
					item.target_port);

			free(item.target_ip);
			free(item.target_port);
			break;
		case RESPONSE_DATA:

			tmp = index(recvstr, '=')+3;

			while ((tmp[0]!='\r') 
					&& (tmp[1]!='\n') 
					&& (tmp[2]!='.') 
					&& (tmp[3]!='\r') 
					&& (tmp[4]!='\n')) {
				str = copy_sub_str_trimmed(tmp, ' ');
				item.stream_id = strtol(str, NULL, 10);
				free(str);

				tmp = index(tmp, ' ')+1;
				str = copy_sub_str_trimmed(tmp, ' ');

				if (!strcmp(str, "NEW\0")) {
					item.status = NEW;
				}
				else if (!strcmp(str, "NEWRESOLVE\0")) {
					item.status = NEWRESOLVE;
				}
				else if (!strcmp(str, "REMAP\0")) {
					item.status = REMAP;
				}
				else if (!strcmp(str, "SENTCONNECT\0")) {
					item.status = SENTCONNECT;
				}
				else if (!strcmp(str, "SENTRESOLVE\0")) {
					item.status = SENTRESOLVE;
				}
				else if (!strcmp(str, "SUCCEEDED\0")) {
					item.status = SUCCEEDED;
				}
				else if (!strcmp(str, "FAILED\0")) {
					item.status = FAILED;
				}
				else if (!strcmp(str, "CLOSED\0")) {
					item.status = CLOSED;
				}
				else if (!strcmp(str, "DETACHED\0")) {
					item.status = DETACHED;
				}
				else {
					return -1;
				}

				free(str);

				tmp = index(tmp, ' ')+1;
				str = copy_sub_str_trimmed(tmp , ' ');
				item.circuit_id = strtol(str, NULL, 10);
				free(str);

				tmp = index(tmp, ' ')+1;
				str = copy_sub_str_trimmed(tmp, ':');
				item.target_ip = malloc(strlen(str)+1);	
				strcpy(item.target_ip, str);
				free(str);

				tmp = index(tmp, ':')+1;
				str = copy_sub_str_trimmed(tmp, '\n');
				item.target_port = malloc(strlen(str)+1);	
				strcpy(item.target_port, str);
				free(str);

				add_to_list(li, 
						item.stream_id,
						item.status,
						item.circuit_id,
						item.target_ip,
						item.target_port);

				free(item.target_ip);
				free(item.target_port);
				tmp = index(tmp, '\n')+1;
			}
			break;
		default:
			break;
	}

	free(recvstr);

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

static int add_to_list(struct LiStreamStatus** li,
		int stream_id,
		E_STREAM_STATUS status,
		int circuit_id,
		char* target_ip,
		char* target_port) {
	int err;

	if (!*li) {
		*li = malloc(sizeof(struct LiStreamStatus));

		if (!*li) {
			return -1;
		}

		err = init_stream_status(&((*li)->s),
				stream_id,
				status,
				circuit_id,
				target_ip,
				target_port);

		if(err<0) {
			return -1;
		}

		(*li)->next = NULL;
		return 0;
	}

	err = add_to_list(&((*li)->next), 
			stream_id, 
			status, 
			circuit_id, 
			target_ip, 
			target_port);

	if (err<0) {
		return -1;
	}

	return 0;
}

E_STREAM_LI_ERROR get_item(struct StreamStatusItem* item, struct LiStreamStatus* li, int i) {
	if (!item) {
		return LI_ERROR;
	}

	if (i==0) {
		item = li->s;
		return ITEM_FOUND;
	}

	get_item(item, li->next, i-1);
}
