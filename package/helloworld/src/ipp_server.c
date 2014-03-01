/*
 * ipp.server.c
 *
 *  Created on: 2013-9-4
 *      Author: openwrt
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#include "stringprocessor.h"
#include "op_action.h"
#define MAXBUF 1024



#define bool int
#define true 1
#define false 0



int lock;  // 1 unlock 0 lock

int autoincreasespeed;
//


typedef struct CLIENT {
	int fd;
	struct sockaddr_in addr;
} CLIENT;

void * write_socket(char *mesg,int newfd);

int main(int argc, char** argv) {
	///
	autoincreasespeed = 0;
	///
	int i, n, maxi = -1;
	int nready;
	int slisten, sockfd, maxfd = -1, connectfd;

	unsigned int myport, lisnum;

	struct sockaddr_in my_addr, addr;
	struct timeval tv;

	socklen_t len;
	fd_set rset, allset;

	char buf[MAXBUF + 1];
	CLIENT client[FD_SETSIZE];

	if (argv[1])
		myport = atoi(argv[1]);
	else
		myport = 5678;

	if (argv[2])
		lisnum = atoi(argv[2]);
	else
		lisnum = FD_SETSIZE;

	if ((slisten = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(myport);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(slisten, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(slisten, lisnum) == -1) {
		perror("listen");
		exit(1);
	}

	for (i = 0; i < FD_SETSIZE; i++) {
		client[i].fd = -1;
	}

	FD_ZERO(&allset);
	FD_SET(slisten, &allset);
	maxfd = slisten;

	printf("Waiting for connections and data...\n");
	while (1) {
		rset = allset;

		tv.tv_sec = 1;
		tv.tv_usec = 0;

		nready = select(maxfd + 1, &rset, NULL, NULL, &tv);

		if (nready == 0)
			continue;
		else if (nready < 0) {
			printf("select failed!\n");
			break;
		} else {
			if (FD_ISSET(slisten,&rset)) // new connection
			{
				len = sizeof(struct sockaddr);
				if ((connectfd
						= accept(slisten, (struct sockaddr*) &addr, &len))
						== -1) {
					perror("accept() error\n");
					continue;
				}
				for (i = 0; i < FD_SETSIZE; i++) {
					if (client[i].fd < 0) {
						client[i].fd = connectfd;
						client[i].addr = addr;
						printf("Yout got a connection from %s.\n", inet_ntoa(
								client[i].addr.sin_addr));
						break;
					}
				}
				if (i == FD_SETSIZE)
					printf("too many connections");
				FD_SET(connectfd,&allset);
				if (connectfd > maxfd)
					maxfd = connectfd;
				if (i > maxi)
					maxi = i;
			} else {
				for (i = 0; i <= maxi; i++) {
					if ((sockfd = client[i].fd) < 0)
						continue;
					if (FD_ISSET(sockfd,&rset)) {
						bzero(buf, MAXBUF + 1);
						if ((n = recv(sockfd, buf, MAXBUF, 0)) > 0) {
							printf("received data:%s\n from %s\n", buf,
									inet_ntoa(client[i].addr.sin_addr));
							OP_MSG recv_msg;
								recv_MSG_parser(buf,&recv_msg);

								//write socket
								//char mesg_str[50];
								//char *mesg = mesg_str;
								char  mesg_str [50] ;
								char *mesg = mesg_str;

								//prepare the meddage
							if (recv_msg.op == OP_GET_CAR_INFO) {
								generater_carInfo(autoincreasespeed++, 80, 1, mesg_str,lock);


							}

							else if(recv_msg.op==OP_LOCK)
							{
								if(recv_msg.extra==UNLOCKING)
								{
									printf("\nunlocking\n");
									lock=UNLOCKED;

								generater_key_resp(mesg_str,lock);
								}
								else if(recv_msg.extra==LOCKING)

								{

									printf("\nlocking\n");
									lock=LOCKED;
									generater_key_resp(mesg_str,lock);
								}
							}

							// now sending
														write_socket(mesg, sockfd);


						} else {
							printf("disconnected by client!\n");
							close(sockfd);
							FD_CLR(sockfd,&allset);
							client[i].fd = -1;
						}
					}
				}
			}
		}
	}
	close(slisten);
}

void * write_socket(char *mesg,int newfd) {

	//send

	//char mesg_str[50];
	//char *mesg = mesg_str;


	int mesg_length = strlen(mesg);
	int sendnum = 0;
	int count = 1;

	printf("%s\n", "staring send info");

	if ((sendnum = send(newfd, mesg, mesg_length, 0)) == -1)
		perror("send error ?**********");
	else {
		printf("sending %d data ", sendnum);

	}

}

