/*
 * GWidgetLayout.hpp
 *
 *  Created on: 19 апр. 2023 г.
 *      Author: serge
 */

#ifndef INC_GWIDGETLAYOUT_HPP_
#define INC_GWIDGETLAYOUT_HPP_

#include "gfx.h"

static inline void GWidgetLayout_PlaceInLine(GWidgetInit *pInit, uint16_t margin)
{
	pInit->g.x += (pInit->g.width + margin);
}

static inline void GWidgetLayout_InitLabelSize(GWidgetInit *pInit, uint16_t maxTextLen, uint16_t back_margin = 1)
{
	pInit->g.height = gdispGetFontMetric(gwinGetDefaultFont(), gFontHeight);
	pInit->g.width = maxTextLen
	                 * (gdispGetFontMetric(gwinGetDefaultFont(), gFontMaxWidth)
	                    + gdispGetFontMetric(gwinGetDefaultFont(), gFontCharPadding));
	pInit->g.width += back_margin;
}

static inline void GWidgetLayout_SetNewTextLine(GWidgetInit *pInit, uint16_t x_pos = 0, uint16_t y_offset = 0)
{
	pInit->g.x = x_pos;
	pInit->g.y += gdispGetFontMetric(gwinGetDefaultFont(), gFontHeight) + y_offset;
}

#endif /* INC_GWIDGETLAYOUT_HPP_ */
