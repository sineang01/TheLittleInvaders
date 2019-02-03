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

#include "GraphicContainer.h"
#include <cassert>

CGraphicContainer::CGraphicContainer(CGraphicItem * pParent):
	CGraphicItem(pParent)
{
}

utils::interfaces::IGraphicContainer * CGraphicContainer::addContainer()
{
	return new CGraphicContainer(this);
}

utils::interfaces::IGraphicBitmap * CGraphicContainer::addBitmap(const utils::CPicture & picture)
{
	return new CGraphicBitmap(picture, this);
}

utils::interfaces::IGraphicTextfield * CGraphicContainer::addTextfield(const char * text)
{
	if (text) return new CGraphicTextfield(text, this);
	else return new CGraphicTextfield(this);
}

void CGraphicContainer::removeItem(IGraphicItem * pItem)
{
	assert(pItem);
	CGraphicItem * pFullItem = dynamic_cast<CGraphicItem *>(pItem);
	pItem->setParent(nullptr);
}

void CGraphicContainer::paint()
{
	const TGraphicItems & graphicItems = items();
	auto it_end = graphicItems.end();
	for (auto it = graphicItems.begin(); it != it_end; ++it)
	{
		dynamic_cast<CGraphicItem *>(*it)->paint();
	}
}
