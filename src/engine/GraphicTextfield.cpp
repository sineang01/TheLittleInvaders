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

#include "Framework.h"
#include "GraphicTextfield.h"
#include <cassert>
#include <cstdarg>

#include "ISystemGlobalEnvironment.h"
extern utils::interfaces::SSystemGlobalEnvironment * g_env;

namespace engine {
    namespace graphic {

        CGraphicTextfield::CGraphicTextfield(CGraphicItem * pParent) : CGraphicItem(pParent)
        {
            setPosition(0, 0);
        }

        CGraphicTextfield::CGraphicTextfield(const char * text, CGraphicItem * pParent)
            : CGraphicItem(pParent)
        {
            setText(text);
            setPosition(0, 0);
        }

        void CGraphicTextfield::setText(const char * format, ...)
        {
            assert(format && format[0]);

            va_list arg_list;
            va_start(arg_list, format);

            char temp[4096];
            vsnprintf_s(temp, 4096, format, arg_list);
            temp[4095] = '\0';

            va_end(arg_list);
            m_text = temp;
        }

        void CGraphicTextfield::draw(int x, int y)
        {
            auto * p_framework = static_cast<CFramework *>(g_env->pFramework);
            assert(p_framework);

            utils::interfaces::IPlatform * p_platform = p_framework->platform();
            assert(p_platform);

            if (!m_text.empty())
            {
                p_platform->drawText(x, y, m_text.c_str());
            }
        }

    } // namespace graphic
} // namespace engine
