/*
 * =====================================================================================
 *
 *       Filename:  torctl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/2010 07:42:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "socket.h"
#include "stdio.h"

int main(int argc, char* argv[]) {
	char* resstr;
	resstr = NULL;
	open_socket();
	send_request("authenticate \"torika\"");
	recv_request(&resstr);
	printf("%s", resstr);
	send_request("getinfo network-status");
	recv_request(&resstr);
	printf("%s", resstr);
	close_socket();
	return 0;
}

