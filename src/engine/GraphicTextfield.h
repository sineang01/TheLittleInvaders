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
#include <IGraphicTextfield.h>

namespace engine {
	namespace graphic {

		class CGraphicTextfield final : public utils::interfaces::IGraphicTextfield, public CGraphicItem
		{
		public:
			CGraphicTextfield(CGraphicItem * pParent = nullptr);
			CGraphicTextfield(const char * text, CGraphicItem * pParent = nullptr);
			CGraphicTextfield(const CGraphicTextfield &) = delete;
			CGraphicTextfield &operator=(const CGraphicTextfield &) = delete;
			virtual ~CGraphicTextfield() override {};

			const char * text() override { return m_text.c_str(); }
			void setText(const char * format, ...) override;

		protected:
			void draw(int x, int y) override;

		private:
			std::string m_text;
		};

	} // namespace graphic
} // namespace engine
