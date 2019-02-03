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

namespace engine {
    namespace graphic {

        CGraphicItem::CGraphicItem(CGraphicItem * pParent) { setParent(pParent); }

        CGraphicItem::~CGraphicItem()
        {
            if (m_pParent != nullptr)
            {
                dynamic_cast<CGraphicItem *>(m_pParent)->removeChild(this);
            }

            TGraphicItems children = m_children;
            if (children.empty())
            {
                return;
            }

            auto it_end = children.end();
            for (auto it = children.begin(); it != it_end; ++it)
            {
                delete *it;
            }

            m_children.clear();
        }

        utils::interfaces::IGraphicItem * CGraphicItem::parent() const { return m_pParent; }

        void CGraphicItem::setParent(IGraphicItem * pParent)
        {
            if (m_pParent == pParent)
            {
                return;
            }

            if (m_pParent != nullptr)
            {
                dynamic_cast<CGraphicItem *>(m_pParent)->removeChild(this);
            }

            m_pParent = pParent;

            if (m_pParent != nullptr)
            {
                dynamic_cast<CGraphicItem *>(m_pParent)->addChild(this);
            }
        }

        void CGraphicItem::setRectangle(const utils::CRectangle & rectangle)
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
            return utils::containers::gPushBackUnique(m_children, pChild);
        }

        bool CGraphicItem::removeChild(CGraphicItem * pChild)
        {
            assert(pChild);
            return utils::containers::gFindAndErase(m_children, pChild);
        }

        bool CGraphicItem::collidesWithItem(const IGraphicItem * pOther, collision_mode mode) const
        {
            assert(pOther);

            utils::CRectangle item_rectangle = shape().translated(draw_offset(this));
            utils::CRectangle other_rectangle = pOther->shape().translated(draw_offset(pOther));
            return collides(item_rectangle, other_rectangle, mode);
        }

        bool CGraphicItem::collidesWithRectangle(const utils::CRectangle & otherRectangle,
                                                 collision_mode mode) const
        {
            assert(otherRectangle.isValid());

            utils::CRectangle item_rectangle = shape().translated(draw_offset(this));
            utils::CRectangle other_rectangle_translated =
                otherRectangle.translated(draw_offset(this));
            return collides(item_rectangle, other_rectangle_translated, mode);
        }

        CGraphicItem::TGraphicItems CGraphicItem::collidingItems(const IGraphicItem * pItem,
                                                                 collision_mode mode) const
        {
            TGraphicItems colliding_items;

            const TGraphicItems & graphic_items = items();
            auto it_end = graphic_items.end();
            for (auto it = graphic_items.begin(); it != it_end; ++it)
            {
                IGraphicItem * p_other_item = (*it);

                if (p_other_item == pItem)
                {
                    continue;
                }

                if (pItem->collidesWithItem(p_other_item, mode))
                {
                    utils::containers::gPushBackUnique(colliding_items, p_other_item);
                }
            }

            return colliding_items;
        }

        CGraphicItem::TGraphicItems CGraphicItem::collidingItems(
            const utils::CRectangle & rectangle,
            collision_mode mode) const
        {
            TGraphicItems colliding_items;

            const TGraphicItems & graphic_items = items();
            auto it_end = graphic_items.end();
            for (auto it = graphic_items.begin(); it != it_end; ++it)
            {
                IGraphicItem * p_item = (*it);

                if (p_item->collidesWithRectangle(rectangle, mode))
                {
                    utils::containers::gPushBackUnique(colliding_items, p_item);
                }
            }

            return colliding_items;
        }

        bool CGraphicItem::collides(const utils::CRectangle & rectangle,
                                    const utils::CRectangle & otherRectangle,
                                    collision_mode mode)
        {
            switch (mode)
            {
                case collision_mode::contain:
                    return rectangle.contains(otherRectangle);

                case collision_mode::intersect_not_contain:
                    return rectangle.intersects(otherRectangle) &&
                           !rectangle.contains(otherRectangle);

                case collision_mode::intersect:
                    return rectangle.intersects(otherRectangle);
            }

            return false;
        }

        utils::CPoint CGraphicItem::draw_offset(const IGraphicItem * pItem)
        {
            utils::CPoint position;

            while (pItem != nullptr)
            {
                IGraphicItem * p_parent = pItem->parent();
                if (p_parent != nullptr)
                {
                    position += p_parent->position();
                }

                pItem = p_parent;
            }

            return position;
        }

    } // namespace graphic
} // namespace engine
