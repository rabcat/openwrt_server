/*
 * op_action.c
 *
 *  Created on: 2013-9-4
 *      Author: openwrt
 */
#include "op_action.h"

void generater_carInfo(int speed_input,int charge_input,int current_input,char mystring [],int  lock)
{
	  sprintf(mystring,"{\"speed\":%d,\"charge\":%d,\"current\":%d,\"lock\":%d}$\n",speed_input,charge_input,current_input,lock);
	  printf("%s\n",mystring);
}

void generater_key_resp(char mystring [],int lock)
{
	if(lock==LOCKED)
	{
		sprintf(mystring,"LOCKED$");
	}
	else if(lock==UNLOCKED)
	{
		sprintf(mystring,"UNLOCKED$");
	}

}
