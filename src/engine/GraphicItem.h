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

#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <IPlatformManager.h>
#include <IGraphicItem.h>
#include <Rectangle.h>

/**
 * @brief CGraphicItem organize themselves in object trees. When a QObject is created with another object as parent, the object will automatically add itself to the parent's items() list. The parent takes ownership of the object; i.e., it will automatically delete its children in its destructor
 */
class CGraphicItem : public virtual IGraphicItem
{
	public:
		/**
		 * @brief Constructs a CGraphicItem with the given pParent item
		 */
		CGraphicItem(CGraphicItem * pParent = nullptr);

		/**
		 * @brief Destroys the CGraphicItem and all its children
		 */
		virtual ~CGraphicItem();

		virtual void paint();

		IGraphicItem * parent() const;
		void setParent(IGraphicItem * pParent);

		CPoint position() const;
		void setPosition(const CPoint & position);
		void setPosition(double x, double y);

		CSize size() const;
		void setSize(const CSize & size);
		void setSize(double w, double h);

		CRectangle rectangle() const;
		void setRectangle(const CRectangle & rectangle);
		void setRectangle(double x, double y, double width, double height);

		const TGraphicItems & items() const;
		virtual CRectangle shape() const;

		bool collidesWithItem(const IGraphicItem * pOther, ECollisionMode mode = eCM_Intersect) const;
		bool collidesWithRectangle(const CRectangle & otherRectangle, ECollisionMode mode = eCM_Intersect) const;
		TGraphicItems collidingItems(const IGraphicItem * pItem, ECollisionMode mode = eCM_Intersect) const;
		TGraphicItems collidingItems(const CRectangle & rectangle, ECollisionMode mode = eCM_Intersect) const;

	protected:
		void draw(const CPoint & position);
		virtual void draw(int x, int y) = 0;

		static bool CGraphicItem::collides(const CRectangle & rectangle, const CRectangle & otherRectangle, ECollisionMode mode = eCM_Intersect);

	private:
		/**
		 * @brief Internal call between CGraphicItem(s) to add a child on another item
		 */
		bool addChild(CGraphicItem * pChild);

		/**
		 * @brief Internal call between CGraphicItem(s) to remove a child from another item
		 */
		bool removeChild(CGraphicItem * pChild);

        /**
         * @brief Calculates the offset between the relative coordinates of the item and the main window 0,0 coordinates
         */
		static CPoint drawOffset(const IGraphicItem * pItem);

	private:
		CGraphicItem(const CGraphicItem &);
		CGraphicItem &operator=(const CGraphicItem &);

	private:
		CRectangle m_rectangle;

		IGraphicItem * m_pParent;
		TGraphicItems m_children;
};

#endif // GRAPHICITEM_H
