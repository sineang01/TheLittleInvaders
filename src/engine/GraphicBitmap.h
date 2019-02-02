/****************************************************************************************
** Copyright (C) 2015 Simone Angeloni
** This file is part of The Little Invaders.
**
** The Little Invaders is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** The Little Invaders is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with The Little Invaders. If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************************/

#ifndef GRAPHICBITMAP_H
#define GRAPHICBITMAP_H

#include <IGraphicBitmap.h>
#include <Picture.h>
#include "GraphicItem.h"

struct ISprite;

class CGraphicBitmap : public IGraphicBitmap, public CGraphicItem
{
	public:
		CGraphicBitmap(const CPicture & picture, CGraphicItem * pParent = NULL);
		virtual ~CGraphicBitmap();

		CRectangle shape() const;

	protected:
		void draw(int x, int y);

	private:
		CGraphicBitmap(const CGraphicBitmap &);
		CGraphicBitmap &operator=(const CGraphicBitmap &);

	private:
		ISprite * m_pSprite;
		CRectangle m_shape;
};

#endif // GRAPHICBITMAP_H
