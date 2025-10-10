/* Copyright (c) 2014 Howard Chu, hyc@symas.com
 *                            All Rights Reserved
 *       Permission is granted to copy or use this program, EXCEPT that it
 *       may not be sold for profit, the copyright notice must be reproduced
 *       on copies, and credit should be given to the author where it is due.
 *       THE AUTHOR MAKES NO WARRANTY AND ACCEPTS NO LIABILITY FOR THIS PROGRAM.
 */
#include "mgrx11.h"
#include "bitx11.h"

#ifndef Min
#define Min(x,y)	((x)>(y)?y:x)
#endif

extern const unsigned char bit_ops[16];
extern int bit_colors[256];
extern void bit_pixmap(BITMAP *map);

