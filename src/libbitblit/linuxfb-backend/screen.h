/* Copyright (c) 2025 erysdren (it/its), contact@erysdren.me
 *                            All Rights Reserved
 *       Permission is granted to copy or use this program, EXCEPT that it
 *       may not be sold for profit, the copyright notice must be reproduced
 *       on copies, and credit should be given to the author where it is due.
 *       THE AUTHOR MAKES NO WARRANTY AND ACCEPTS NO LIABILITY FOR THIS PROGRAM.
 */
#define DATA unsigned char

#include <mgr/bitblit.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define LOGBITS 3
#define BITS (~(~(unsigned)0 << LOGBITS))

#define bit_linesize(wide, depth) ((((depth) * (wide) + BITS) & ~BITS) >> 3)

#define BIT_LINE(x) ((((x)->primary->depth * (x)->primary->wide + BITS) & ~BITS) >> LOGBITS)

#define BIT_Size(wide,high,depth) (((((depth)*(wide)+BITS)&~BITS)*(high))>>3)

typedef struct mgr_linuxfb_ctx {
	struct fb_var_screeninfo varinfo;
	struct fb_fix_screeninfo fixinfo;
	void *buf;
	size_t buflen;
	int fd;
} mgr_linuxfb_ctx_t;
