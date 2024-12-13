#include "gfx_extended.h"
#include "../ugfx_2.9/src/gfx_mk.c"


void gdispGDrawPixelFast(GDisplay *g, gCoord x, gCoord y, gColor color) {
	g->p.x		= x;
	g->p.y		= y;
	g->p.color	= color;
	drawpixel_clip(g);
	autoflush(g);
}

void gdispMutexEnter(GDisplay *g) {
	MUTEX_ENTER(g);
}

void gdispMutexExit(GDisplay *g) {
	MUTEX_EXIT(g);
}


void gdispGFillAreaFast(GDisplay *g, gCoord x, gCoord y, gCoord cx, gCoord cy, gColor color) {
	g->p.x = x;
	g->p.y = y;
	g->p.cx = cx;
	g->p.cy = cy;
	g->p.color = color;
	TEST_CLIP_AREA(g) {
		fillarea(g);
	}
	autoflush_stopdone(g);
}
