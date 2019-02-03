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
#include "GraphicBitmap.h"
#include <cassert>

#include "ISystemGlobalEnvironment.h"
extern utils::interfaces::SSystemGlobalEnvironment * g_env;

namespace engine {
	namespace graphic {

		CGraphicBitmap::CGraphicBitmap(const utils::CPicture & picture, CGraphicItem * pParent)
			:CGraphicItem(pParent)
			,m_shape(picture.shape())
		{
			assert(picture.isValid());

			auto * p_framework = static_cast<CFramework*>(g_env->pFramework);
			assert(p_framework);

			utils::interfaces::IPlatform * p_platform = p_framework->platform();
			assert(p_platform);

			m_pSprite = p_platform->createSprite(picture.image());
			assert(m_pSprite);

			setPosition(0, 0);
			setSize(picture.size());
		}

		CGraphicBitmap::~CGraphicBitmap()
		{
			// All the sprites are deferred destroyed
			auto * p_framework = static_cast<CFramework*>(g_env->pFramework);
			assert(p_framework);

			p_framework->destroySprite(m_pSprite);
		}

		void CGraphicBitmap::draw(int x, int y)
		{
			m_pSprite->draw(x, y);
		}

	} // namespace graphic
} // namespace engine
