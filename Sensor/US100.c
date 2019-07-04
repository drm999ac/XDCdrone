/*
 * US100.c
 *
 *  Created on: 2019Äê7ÔÂ4ÈÕ
 *      Author: Crusader
 */


#include "US100.h"

void RequireUS100data(void)
{
    unsigned char US100Buff[1];
    US100Buff[0]  = 0x55;
    scid_msg(US100Buff);
}

