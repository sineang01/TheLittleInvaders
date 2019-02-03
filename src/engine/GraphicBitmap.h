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
#include "GraphicItem.h"
#include <IGraphicBitmap.h>
#include <Picture.h>

namespace utils {
	namespace interfaces {
		struct ISprite;
	}
}

class CGraphicBitmap final : public utils::interfaces::IGraphicBitmap, public CGraphicItem
{
	public:
		CGraphicBitmap(const utils::CPicture & picture, CGraphicItem * pParent = nullptr);
		virtual ~CGraphicBitmap();
		CGraphicBitmap(const CGraphicBitmap &) = delete;
		CGraphicBitmap &operator=(const CGraphicBitmap &) = delete;

		utils::CRectangle shape() const;

	protected:
		void draw(int x, int y);

	private:
		utils::interfaces::ISprite * m_pSprite;
		utils::CRectangle m_shape;
};
