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

#include "GraphicItem.h"
#include <ContainersUtils.h>
#include <cassert>

CGraphicItem::CGraphicItem(CGraphicItem * pParent):
	m_pParent(nullptr)
{
	setParent(pParent);
}

CGraphicItem::~CGraphicItem()
{
	if (m_pParent)
		dynamic_cast<CGraphicItem*>(m_pParent)->removeChild(this);

	TGraphicItems children = m_children;
	if (children.empty())
		return;

	for (TGraphicItems::iterator it = children.begin(); it != children.end(); ++it)
	{
		delete *it;
	}

	m_children.clear();
}

IGraphicItem * CGraphicItem::parent() const
{
	return m_pParent;
}

void CGraphicItem::setParent(IGraphicItem * pParent)
{
	if (m_pParent == pParent)
		return;

	if (m_pParent)
		dynamic_cast<CGraphicItem*>(m_pParent)->removeChild(this);

	m_pParent = pParent;

	if (m_pParent)
		dynamic_cast<CGraphicItem*>(m_pParent)->addChild(this);
}

CPoint CGraphicItem::position() const
{
	return m_rectangle.position();
}

void CGraphicItem::setPosition(const CPoint & position)
{
	m_rectangle.setPosition(position);
}

void CGraphicItem::setPosition(double x, double y)
{
	m_rectangle.setPosition(x, y);
}

CSize CGraphicItem::size() const
{
	return m_rectangle.size();
}

void CGraphicItem::setSize(const CSize & size)
{
	m_rectangle.setSize(size);
}

void CGraphicItem::setSize(double w, double h)
{
	m_rectangle.setSize(CSize(w, h));
}

CRectangle CGraphicItem::rectangle() const
{
	return m_rectangle;
}

void CGraphicItem::setRectangle(const CRectangle & rectangle)
{
	m_rectangle.setPosition(rectangle.position());
	m_rectangle.setSize(rectangle.size());
}

void CGraphicItem::setRectangle(double x, double y, double width, double height)
{
	m_rectangle.setX(x);
	m_rectangle.setY(y);
	m_rectangle.setWidth(width);
	m_rectangle.setHeight(height);
}

bool CGraphicItem::addChild(CGraphicItem * pChild)
{
	assert(pChild);
	return containers::gPushBackUnique(m_children, pChild);
}

bool CGraphicItem::removeChild(CGraphicItem * pChild)
{
	assert(pChild);
	return containers::gFindAndErase(m_children, pChild);
}

const CGraphicItem::TGraphicItems & CGraphicItem::items() const
{
	return m_children;
}

CRectangle CGraphicItem::shape() const
{
	return m_rectangle;
}

bool CGraphicItem::collidesWithItem(const IGraphicItem * pOther, ECollisionMode mode) const
{
	assert(pOther);

	CRectangle itemRectangle = shape().translated(drawOffset(this));
	CRectangle otherRectangle = pOther->shape().translated(drawOffset(pOther));
	return collides(itemRectangle, otherRectangle, mode);
}

bool CGraphicItem::collidesWithRectangle(const CRectangle & otherRectangle, ECollisionMode mode) const
{
	assert(otherRectangle.isValid());

	CRectangle itemRectangle = shape().translated(drawOffset(this));
	CRectangle otherRectangleTranslated = otherRectangle.translated(drawOffset(this));
	return collides(itemRectangle, otherRectangleTranslated, mode);
}

CGraphicItem::TGraphicItems CGraphicItem::collidingItems(const IGraphicItem * pItem, ECollisionMode mode) const
{
	TGraphicItems collidingItems;

	const TGraphicItems & graphicItems = items();
	TGraphicItems::const_iterator it_end = graphicItems.end();
	for (TGraphicItems::const_iterator it = graphicItems.begin(); it != it_end; ++it)
	{
		IGraphicItem * pOtherItem = (*it);

		if (pOtherItem == pItem)
			continue;

		if (pItem->collidesWithItem(pOtherItem, mode))
			containers::gPushBackUnique(collidingItems, pOtherItem);
	}

	return collidingItems;
}

CGraphicItem::TGraphicItems CGraphicItem::collidingItems(const CRectangle & rectangle, ECollisionMode mode) const
{
	TGraphicItems collidingItems;

	const TGraphicItems & graphicItems = items();
	TGraphicItems::const_iterator it_end = graphicItems.end();
	for (TGraphicItems::const_iterator it = graphicItems.begin(); it != it_end; ++it)
	{
		IGraphicItem * pItem = (*it);

		if (pItem->collidesWithRectangle(rectangle, mode))
			containers::gPushBackUnique(collidingItems, pItem);
	}

	return collidingItems;
}

bool CGraphicItem::collides(const CRectangle & rectangle, const CRectangle & otherRectangle, ECollisionMode mode)
{
	switch(mode)
	{
		case eCM_Contain:
			return rectangle.contains(otherRectangle);

		case eCM_IntersectNotContain:
			return rectangle.intersects(otherRectangle) && !rectangle.contains(otherRectangle);

		case eCM_Intersect:
			return rectangle.intersects(otherRectangle);
	}

	return false;
}

void CGraphicItem::paint()
{
	draw(drawOffset(this) + position());
}

void CGraphicItem::draw(const CPoint & position)
{
	draw((int)position.x(), (int)position.y());
}

CPoint CGraphicItem::drawOffset(const IGraphicItem * pItem)
{
	CPoint position;

	while(pItem != nullptr)
	{
		IGraphicItem * pParent = pItem->parent();
		if (pParent)
			position += pParent->position();

		pItem = pParent;
	}

	return position;
}
