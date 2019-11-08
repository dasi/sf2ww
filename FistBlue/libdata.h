/*
 *  libdata.h
 *  GLUTBasics
 *
 *  Created by Ben on 4/01/11.
 *  Copyright 2011 Ben Torkington. All rights reserved.
 *
 */



/* Scores in BCD */

static const int data_530c[] = {
	0x00000100L,
	0x00000200L,
	0x00000500L,
	0x00001000L,
	0x00002000L,
	0x00005000L,
	0x00006000L,
	0x00008000L,
	0x00010000L,
	0x00020000L,
	0x00030000L,
	0x00100000L,
	0x01000000L,
};




static const u16 data_d578[] = {		// same as data_7e900
	0, 0x8197, 0x81b7, 0x8199,
	0x819f, 0x81bf, 0x81cf, 0x817f, 0x81af,
	0x818f, 0x817e, 0x816f, 0x816e
};




/* used in sub_307e */

static const char data_956f2[12][16][32] = {
	{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	},{ 
		{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  },
		{ 14, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1,  },
		{ 20, 18, 16, 14, 13, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1,  },
		{ 25, 23, 21, 20, 18, 16, 15, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 1,  },
		{ 26, 24, 22, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1,  },
		{ 32, 30, 28, 26, 24, 22, 21, 20, 19, 18, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 9, 8, 6, 4, 2, 1, 1, 1, 1,  },
		{ 35, 33, 31, 29, 27, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 13, 12, 11, 10, 9, 7, 6, 4, 2, 1, 1,  },
		{ 41, 39, 37, 35, 33, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 14, 12, 10, 8, 6, 4, 2, 1, 1, 1,  },
		{ 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -2, -2,  },
		{ 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -2,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -4, -4, -4, -4, -6, -6,  },
		{ 7, 7, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 0, -1, -1, -1, -3, -3, -3, -3, -3, -3, -5, -5, -5, -5, -7, -7,  },
		{ 8, 8, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, -2, -2, -2, -4, -4, -4, -4, -4, -4, -6, -6, -6, -6, -8, -8,  },
		{ 9, 9, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0, -3, -3, -3, -5, -5, -5, -5, -5, -5, -7, -7, -7, -7, -9, -9,  },
		{ 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 0, 0, -4, -4, -4, -6, -6, -6, -6, -6, -6, -8, -8, -8, -8, -10, -10,  },
	}, };
/* next address 00096f0a */

/**
 One bit in 512 for 512-Guard and 512-Special
 sf2ua: 0x98d82
 */
static const u8 data_98d82[0x40]= {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
	
