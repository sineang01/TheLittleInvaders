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

#ifndef GRAPHICCONTAINER_H
#define GRAPHICCONTAINER_H

#include <IGraphicContainer.h>
#include "GraphicItem.h"
#include "GraphicBitmap.h"
#include "GraphicTextfield.h"

class CGraphicContainer : public IGraphicContainer, public CGraphicItem
{
	public:
		CGraphicContainer(CGraphicItem * pParent = nullptr);
		virtual ~CGraphicContainer() {};

		void paint();

		IGraphicContainer * addContainer();
		IGraphicBitmap * addBitmap(const CPicture & picture);
		IGraphicTextfield * addTextfield(const char * text = nullptr);

		void removeItem(IGraphicItem * pItem);

	private:
		CGraphicContainer(const CGraphicContainer &);
		CGraphicContainer &operator=(const CGraphicContainer &);

	protected:
        virtual void draw(int x, int y) {}
};

#endif //GRAPHICCONTAINER_H

