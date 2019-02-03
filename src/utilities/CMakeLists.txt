cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project(utilities VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES_INTERFACES
	IFramework.h
	IGame.h
	IGraphicBitmap.h
	IGraphicContainer.h
	IGraphicItem.h
	IGraphicTextfield.h
	InputKey.h
	IPlatform.h
	IPlatformManager.h
	ISystemGlobalEnvironment.h
	IVariable.h
	IVariablesManager.h)

set(SOURCES_MISC
	BaseListenerHandler.h
	ContainersUtils.h
	CSVReader.cpp
	CSVReader.h
	GameTimer.cpp
	GameTimer.h
	LibraryHandler.cpp
	LibraryHandler.h
	MathUtils.h
	Path.cpp
	Path.h)

set(SOURCES_GRAPHIC
	Picture.cpp
	Picture.h
	Point.cpp
	Point.h
	Rectangle.cpp
	Rectangle.h
	Size.cpp
	Size.h)

add_library(${PROJECT_NAME} ${SOURCES_INTERFACES} ${SOURCES_MISC} ${SOURCES_GRAPHIC}) 
source_group("src\\interface" FILES ${SOURCES_INTERFACES})
source_group("src\\miscellaneous" FILES ${SOURCES_MISC})
source_group("src\\graphic" FILES ${SOURCES_GRAPHIC})

# Compile options (warnings)
#set_warning_level()
#set_warning_as_error()
