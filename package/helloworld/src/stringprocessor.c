/*
 * stringprocessor.c
 *
 *  Created on: 2013-9-4
 *      Author: openwrt
 */


#include "stringprocessor.h"


void recv_MSG_parser(char * str_source, OP_MSG *msg)
{


	//char  *str_source ="KEY 10 10 88888888";
	char type [STR_TYPE_LEN+1]={0};
	char action [STR_ACTION_LEN+1]={0};
	char action_extra [STR_ACTION_EXTRA_LEN+1]={0};
	char password [STR_PW_LEN+1]={0};

	strncpy(type, str_source, STR_TYPE_LEN);
	strncpy(action,str_source+STR_TYPE_LEN+1,STR_ACTION_LEN);
	strncpy(action_extra,str_source+STR_TYPE_LEN+STR_ACTION_LEN+2,STR_ACTION_EXTRA_LEN);
	strncpy(password,str_source+STR_TYPE_LEN+STR_ACTION_LEN+STR_ACTION_EXTRA_LEN+3,STR_PW_LEN);

	//printf("type:%s\n",type);

	//printf("action:%s\n",action);
	//printf("action_extra:%s\n",action_extra);
	//printf("pass:%s\n",password);


	if(strcmp(type,"KEY")==0)
	{
		(*msg).type=KEY;
		//printf("from key");
	}
	else
	{
		(*msg).type=TABLET;
		//printf("from tablet");
	}
	msg->op=atoi(action);
	msg->extra=atoi(action_extra);
	strcpy(msg->password,password);

	printf("MSG %d %d %d %s",msg->type,msg->op,msg->extra,msg->password);
	//return 0;
}



