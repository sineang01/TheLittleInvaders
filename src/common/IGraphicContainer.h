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

#ifndef IGRAPHICCONTAINER_H
#define IGRAPHICCONTAINER_H

#include "IGraphicItem.h"
#include "Picture.h"

struct IGraphicBitmap;
struct IGraphicTextfield;

struct IGraphicContainer : public virtual IGraphicItem
{
	virtual IGraphicContainer * addContainer() = 0;
	virtual IGraphicBitmap * addBitmap(const CPicture & picture) = 0;
	virtual IGraphicTextfield * addTextfield(const char * text = NULL) = 0;

	virtual void removeItem(IGraphicItem * pItem) = 0;

	virtual ~IGraphicContainer() {};
};

#endif // IGRAPHICCONTAINER_H

