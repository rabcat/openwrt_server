/*
 * stringprocessor.h
 *
 *  Created on: 2013-9-4
 *      Author: openwrt
 */

#ifndef STRINGPROCESSOR_H_
#define STRINGPROCESSOR_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_TYPE_LEN 3
#define STR_ACTION_LEN 2
#define STR_ACTION_EXTRA_LEN 2
#define STR_PW_LEN 8

#define bool int
#define true 1
#define false 0

#define TABLET 0
#define KEY 1



typedef struct OP_MSG {
    int op;
    int extra;
    int  type;
    char  password[STR_PW_LEN+1];

}OP_MSG;

void jsonStringGenerator(int speed_input,int charge_input,int current_input,char mystring [],int  unlock);
void recv_MSG_parser(char * str_source, OP_MSG *msg);

#endif /* STRINGPROCESSOR_H_ */
