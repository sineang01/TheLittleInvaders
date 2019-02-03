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

#pragma once
#include "Rectangle.h"
#include <vector>

namespace utils {
	namespace interfaces {

		struct IGraphicItem
		{
			typedef std::vector<IGraphicItem*> TGraphicItems;

			enum ECollisionMode
			{
				eCM_Contain = 0,            /* The output list contains only items whose shapes are fully contained in the shape of the current item */
				eCM_IntersectNotContain,    /* The output list contains only items whose shapes interesct with the one of the current item, but is not fully contained */
				eCM_Intersect               /* The output list contains only items whose shapes are intersecting at least by 1 pixel with the one of the current item */
			};

			virtual IGraphicItem * parent() const = 0;
			virtual void setParent(IGraphicItem * pParent) = 0;

			virtual CPoint position() const = 0;
			virtual void setPosition(const CPoint & position) = 0;
			virtual void setPosition(double x, double y) = 0;

			virtual CSize size() const = 0;
			virtual void setSize(const CSize & size) = 0;
			virtual void setSize(double w, double h) = 0;

			virtual CRectangle rectangle() const = 0;
			virtual void setRectangle(const CRectangle & rectangle) = 0;
			virtual void setRectangle(double x, double y, double width, double height) = 0;

			virtual const TGraphicItems & items() const = 0;
			virtual CRectangle shape() const = 0;

			virtual bool collidesWithItem(const IGraphicItem * pOther, ECollisionMode mode = eCM_Intersect) const = 0;
			virtual bool collidesWithRectangle(const CRectangle & otherRectangle, ECollisionMode mode = eCM_Intersect) const = 0;
			virtual TGraphicItems collidingItems(const IGraphicItem * pItem, ECollisionMode mode = eCM_Intersect) const = 0;
			virtual TGraphicItems collidingItems(const CRectangle & rectangle, ECollisionMode mode = eCM_Intersect) const = 0;

			virtual ~IGraphicItem() {};
		};

	} // namespace interfaces
} // namespace utils
