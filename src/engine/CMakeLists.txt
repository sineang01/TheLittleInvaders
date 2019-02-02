cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project(engine VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCEC_GRAPHICVIEW_FRAMEWORK
	GraphicBitmap.cpp
	GraphicBitmap.h
	GraphicContainer.cpp
	GraphicContainer.h
	GraphicItem.cpp
	GraphicItem.h
	GraphicTextfield.cpp
	GraphicTextfield.h)

set(SOURCES_PLATFORMS
	EasyPlatform.cpp
	EasyPlatform.h
	PlatformFactory.cpp
	PlatformFactory.h)

set(SOURCES_VARIABLES
	VariablesManager.cpp
	VariablesManager.h)

set(SOURCES_OTHERS
	EngineDll.cpp
	Framework.cpp
	Framework.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES_OTHERS} ${SOURCEC_GRAPHICVIEW_FRAMEWORK} ${SOURCES_PLATFORMS} ${SOURCES_VARIABLES}) 
source_group("src" FILES ${SOURCES_OTHERS})
source_group("src\\graphicview" FILES ${SOURCEC_GRAPHICVIEW_FRAMEWORK})
source_group("src\\platforms" FILES ${SOURCES_PLATFORMS})
source_group("src\\variables" FILES ${SOURCES_VARIABLES})

add_dependencies(${PROJECT_NAME} common)
target_link_libraries(${PROJECT_NAME} common)
target_include_directories(${PROJECT_NAME} PUBLIC ${common_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME}
	DESTINATION ${TheLittleInvaders_SOURCE_DIR}/output)

# Compile options (warnings)
#set_warning_level()
#set_warning_as_error()
