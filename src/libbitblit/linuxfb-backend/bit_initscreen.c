/*                        Copyright (c) 1987 Bellcore
 *                            All Rights Reserved
 *       Permission is granted to copy or use this program, EXCEPT that it
 *       may not be sold for profit, the copyright notice must be reproduced
 *       on copies, and credit should be given to Bellcore where it is due.
 *       BELLCORE MAKES NO WARRANTY AND ACCEPTS NO LIABILITY FOR THIS PROGRAM.
 */

#include "screen.h"

DATA *
bit_initscreen(char *name, int *width, int *height, unsigned char *depth, void **device)
{
	mgr_linuxfb_ctx_t *ctx = NULL;

	ctx = malloc(sizeof(*ctx));
	if (!ctx)
		return NULL;

	memset(ctx, 0, sizeof(*ctx));

	ctx->fd = open(name, O_RDWR);
	if (ctx->fd < 0)
	{
		free(ctx);
		return NULL;
	}

	if (ioctl(ctx->fd, FBIOGET_VSCREENINFO, &ctx->varinfo) != 0 ||
		ioctl(ctx->fd, FBIOGET_FSCREENINFO, &ctx->fixinfo) != 0)
	{
		close(ctx->fd);
		free(ctx);
		return NULL;
	}

	ctx->buflen = ctx->varinfo.yres_virtual * ctx->fixinfo.line_length;
	ctx->buf = mmap(NULL, ctx->buflen, PROT_READ | PROT_WRITE, MAP_SHARED, ctx->fd, 0);
	if (ctx->buf == MAP_FAILED)
	{
		close(ctx->fd);
		free(ctx);
		return NULL;
	}

	*device = (void *)ctx;

	return NULL;
}

void display_close(BITMAP *bitmap)
{
	mgr_linuxfb_ctx_t *ctx = (mgr_linuxfb_ctx_t *)bitmap->deviceinfo;
	if (ctx)
	{
		if (ctx->fd >= 0)
			close(ctx->fd);

		if (ctx->buf != NULL && ctx->buf != MAP_FAILED)
			munmap(ctx->buf, ctx->buflen);

		free(ctx);
	}
}
