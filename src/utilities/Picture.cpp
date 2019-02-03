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

#include "Path.h"
#include "Picture.h"
#include <cassert>
#include <fstream>

namespace utils {

    CPicture::CPicture(const char * imagePath) { setImage(imagePath); }

    CPicture::CPicture(const char * imagePath, const CRectangle & shape) : m_shape(shape)
    {
        setImage(imagePath);
    }

    void CPicture::setImage(const char * imagePath)
    {
        assert(imagePath && imagePath[0]);
        m_imagePath = imagePath;

        // m_size = CSize(32, 32);
        assert(readImage());
    }

    bool CPicture::readImage()
    {
        std::string path = path_utils::executablePath();
        path += "\\";
        path += m_imagePath;

        std::ifstream file_input(path.c_str(), std::ios::in | std::ios::binary);
        if (!file_input.is_open())
        {
            return false;
        }

        static const int s_format_size = 2;
        char file_format[s_format_size + 1] = {'\0'};
        file_input.read(file_format, s_format_size);
        if (strncmp(file_format, "BM", s_format_size) != 0)
        {
            return false;
        }

        file_input.seekg(0x12, std::ios::beg);
        unsigned int width = 0;
        file_input.read((char *)&width, sizeof(unsigned int));

        unsigned int height = 0;
        file_input.read((char *)&height, sizeof(unsigned int));

        m_size = CSize(width, height);
        file_input.close();

        return true;
    }

} // namespace utils
