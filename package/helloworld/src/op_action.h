/*
 * op_action.h
 *
 *  Created on: 2013-9-4
 *      Author: openwrt
 */

#ifndef OP_ACTION_H_
#define OP_ACTION_H_

#define OP_GET_CAR_INFO 1
#define OP_LOCK 2

#define LOCKING 0
#define UNLOCKING 1
#define LOCKED 0
#define UNLOCKED 1

void generater_carInfo(int speed_input,int charge_input,int current_input,char mystring [],int  lock);

void generater_key_resp(char mystring [],int lock);
#endif /* OP_ACTION_H_ */
