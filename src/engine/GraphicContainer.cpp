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

#include "stdafx.h"
#include "GraphicContainer.h"

CGraphicContainer::CGraphicContainer(CGraphicItem * pParent):
	CGraphicItem(pParent)
{
}

IGraphicContainer * CGraphicContainer::addContainer()
{
	return new CGraphicContainer(this);
}

IGraphicBitmap * CGraphicContainer::addBitmap(const CPicture & picture)
{
	return new CGraphicBitmap(picture, this);
}

IGraphicTextfield * CGraphicContainer::addTextfield(const char * text)
{
	if (text) return new CGraphicTextfield(text, this);
	else return new CGraphicTextfield(this);
}

void CGraphicContainer::removeItem(IGraphicItem * pItem)
{
	assert(pItem);
	CGraphicItem * pFullItem = dynamic_cast<CGraphicItem *>(pItem);
	pItem->setParent(NULL);
}

void CGraphicContainer::paint()
{
	const TGraphicItems & graphicItems = items();
	TGraphicItems::const_iterator it_end = graphicItems.end();
	for (TGraphicItems::const_iterator it = graphicItems.begin(); it != it_end; ++it)
	{
		dynamic_cast<CGraphicItem *>(*it)->paint();
	}
}
