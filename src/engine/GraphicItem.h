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
#include <IGraphicItem.h>
#include <IPlatformManager.h>
#include <Rectangle.h>

namespace engine {
	namespace graphic {

		/**
		 * @brief CGraphicItem organize themselves in object trees. When a QObject is created with another object as parent, the object will automatically add itself to the parent's items() list. The parent takes ownership of the object; i.e., it will automatically delete its children in its destructor
		 */
		class CGraphicItem : public virtual utils::interfaces::IGraphicItem
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
			CGraphicItem(const CGraphicItem &) = delete;
			CGraphicItem &operator=(const CGraphicItem &) = delete;

			virtual void paint() { draw(drawOffset(this) + position()); }

			utils::interfaces::IGraphicItem * parent() const;
			void setParent(utils::interfaces::IGraphicItem * pParent);

			utils::CPoint position() const { return m_rectangle.position(); }
			void setPosition(const utils::CPoint & position) { m_rectangle.setPosition(position); }
			void setPosition(double x, double y) { m_rectangle.setPosition(x, y); }

			utils::CSize size() const { return m_rectangle.size(); }
			void setSize(const utils::CSize & size) { m_rectangle.setSize(size); }
			void setSize(double w, double h) { m_rectangle.setSize(utils::CSize(w, h)); }

			utils::CRectangle rectangle() const { return m_rectangle; }
			void setRectangle(const utils::CRectangle & rectangle);
			void setRectangle(double x, double y, double width, double height);

			const TGraphicItems & items() const { return m_children; }
			virtual utils::CRectangle shape() const { return m_rectangle; }

			bool collidesWithItem(const IGraphicItem * pOther, collision_mode mode = collision_mode::intersect) const;
			bool collidesWithRectangle(const utils::CRectangle & otherRectangle, collision_mode mode = collision_mode::intersect) const;
			TGraphicItems collidingItems(const IGraphicItem * pItem, collision_mode mode = collision_mode::intersect) const;
			TGraphicItems collidingItems(const utils::CRectangle & rectangle, collision_mode mode = collision_mode::intersect) const;

		protected:
			void draw(const utils::CPoint & position) { draw((int)position.x(), (int)position.y()); }
			virtual void draw(int x, int y) = 0;

			static bool CGraphicItem::collides(const utils::CRectangle & rectangle, const utils::CRectangle & otherRectangle, collision_mode mode = collision_mode::intersect);

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
			static utils::CPoint drawOffset(const IGraphicItem * pItem);

		private:
			utils::CRectangle m_rectangle;

			IGraphicItem * m_pParent{ nullptr };
			TGraphicItems m_children;
		};
	
	} // namespace graphic
} // namespace engine
