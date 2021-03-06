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
#include "GraphicBitmap.h"
#include "GraphicItem.h"
#include "GraphicTextfield.h"
#include <IGraphicContainer.h>

namespace engine {
	namespace graphic {

		class CGraphicContainer final : public utils::interfaces::IGraphicContainer, public CGraphicItem
		{
		public:
			CGraphicContainer(CGraphicItem * pParent = nullptr);
			CGraphicContainer(const CGraphicContainer &) = delete;
			CGraphicContainer &operator=(const CGraphicContainer &) = delete;
			virtual ~CGraphicContainer() override {};

			// CGraphicItem
			void paint() override;
			//~CGraphicItem

			// IGraphicContainer
			inline utils::interfaces::IGraphicContainer * addContainer() override { return new CGraphicContainer(this); }
			inline utils::interfaces::IGraphicBitmap * addBitmap(const utils::CPicture & picture) override { return new CGraphicBitmap(picture, this); }
			utils::interfaces::IGraphicTextfield * addTextfield(const char * text = nullptr) override;
			void removeItem(IGraphicItem * pItem) override;
			//~IGraphicContainer

		protected:
			// CGraphicItem
			virtual void draw(int x, int y) override {}
			//~CGraphicItem
		};

	} // namespace graphic
} // namespace engine
