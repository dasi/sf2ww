/*
 *  coinage.h
 *  MT2
 *
 *  Created by Ben on 19/11/11.
 *  Copyright 2011 Ben Torkington. All rights reserved.
 *
 */
#ifndef _SF2_COINAGE
#define _SF2_COINAGE

void task_creditscreen(void);
void check_coin_lockout(void);
void decode_coincosts(void);
void sub_1fe2(void);
void sub_1ed0(void);

struct coinslot {
	char x0000;
	char x0001;
	char x0002;
	char x0003;
	char nCoins;
	char nCredits;
	char x0006;
	char x0007;
};

typedef struct coinslot Coinslot;

#endif