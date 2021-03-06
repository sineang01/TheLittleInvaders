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
#include "GraphicItem.h"
#include <cassert>

namespace engine {
    namespace graphic {

        CGraphicContainer::CGraphicContainer(CGraphicItem * pParent) : CGraphicItem(pParent) {}

        utils::interfaces::IGraphicTextfield * CGraphicContainer::addTextfield(const char * text)
        {
            if (text != nullptr)
            {
                return new CGraphicTextfield(text, this);
            }

            return new CGraphicTextfield(this);
        }

        void CGraphicContainer::removeItem(IGraphicItem * pItem)
        {
            assert(pItem);
            dynamic_cast<CGraphicItem *>(pItem)->setParent(nullptr);
        }

        void CGraphicContainer::paint()
        {
            const TGraphicItems & graphic_items = items();
            auto it_end = graphic_items.end();
            for (auto it = graphic_items.begin(); it != it_end; ++it)
            {
                dynamic_cast<CGraphicItem *>(*it)->paint();
            }
        }

    } // namespace graphic
} // namespace engine
