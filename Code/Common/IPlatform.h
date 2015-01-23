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

#ifndef IPLATFORM_H
#define IPLATFORM_H

struct ISprite
{
	/**
	 * @brief Destroys the sprite instance
	 */
	virtual void destroy() = 0;

	/**
	 * @brief Draw the sprite at the given position. 
	 * Valid coordinates are between (0,0) (upper left) and (width-32, height-32) (lower right).
	 * (All sprites are 32*32 pixels, clipping is not supported)
	*/
	virtual void draw(int x, int y) = 0;
};

struct IPlatform 
{
	/**
	 * @brief A type type for creating IPlatform instances
	 */
	typedef IPlatform *(__cdecl TEntryFunction)();

	/**
	 * @brief Destroys the platform instance
	 */
	virtual void destroy() = 0;

	/**
	 * @brief Creates the main window. Returns true on success.
	 */
	virtual bool init(int width, int height) = 0;

	/**
	 * @brief Clears the screen and draws all sprites and texts which have been drawn since the last update call.
	 * @return If update returns false, the application should terminate.
	 */ 
	virtual bool update() = 0;

	/**
	 * @brief Create a sprite given a string. All sprites are 32*32 pixels.
	 */
	virtual ISprite* createSprite(const char* name) = 0;

	/**
	 * @brief Draws the given text.
	 */
	virtual void drawText(int x, int y, const char* msg) = 0;

	/**
	 * @brief Return the total time spent in the game, in seconds.
	 */
	virtual float getElapsedTime() = 0;

	struct KeyStatus
	{
		bool fire;	/* space */
		bool left;	/* left arrow */
		bool right;	/* right arrow */
	};

	/**
	 * @brief Returns the keyboard status. If a flag is set, the corresponding key is being held down.
	 */
	virtual void getKeyStatus(KeyStatus& keys) = 0;
};

#endif // IPLATFORM_H
