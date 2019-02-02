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
#include "BaseListenerHandler.h"
#include "IVariablesManager.h"
#include "InputKey.h"
#include "Size.h"

struct IGraphicContainer;
struct SSystemGlobalEnvironment;

struct IFrameworkListener
{
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onInput(CInputKey key, float deltaTime) = 0;
};

struct IFramework : public CBaseListenerHandler<IFrameworkListener>
{
	typedef IFramework *(*TEntryFunctionCreate)(SSystemGlobalEnvironment*);
	typedef void (*TEntryFunctionDestroy)();

  /**
    * @brief Initialize the framework using the given parameters
    * @return true if the platform is successfully initialized, otherwise false
    */
	virtual bool init() = 0;
		
  /**
    * @brief Enters the main event loop. It is necessary to call this function to start event handling
    */
	virtual int exec() = 0;

    /**
     * @brief Retrieves the total elaptsed time since the start up
     */
	virtual float elapsedTime() const = 0;

  /**
    * @brief Retreives the platform window
    */
	virtual IGraphicContainer * window() const = 0;

  /**
    * @brief Generates a random value between 0 and maxValue
    */
	virtual unsigned int random(size_t maxValue) const = 0;

	/**
		* @brief Retreives the application path
		*/
	virtual const char * applicationPath() const = 0;

	/**
		* @brief Retreives the variables manager
		*/
	virtual IVariablesManager * variablesManager() const = 0;
};
