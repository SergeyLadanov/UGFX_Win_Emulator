#ifndef __GFX_EXTENDED_H__
#define __GFX_EXTENDED_H__

#include "gfx.h"

#ifdef __cplusplus
extern "C"
{
#endif

void gdispGDrawPixelFast(GDisplay *g, gCoord x, gCoord y, gColor color);

void gdispMutexEnter(GDisplay *g);

void gdispMutexExit(GDisplay *g);

void gdispGFillAreaFast(GDisplay *g, gCoord x, gCoord y, gCoord cx, gCoord cy, gColor color);

#ifdef __cplusplus
}
#endif

#endif /* __GFX_EXTENDED_H__ */
