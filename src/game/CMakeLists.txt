cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project(game VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCEC_STATES
	GameStateCommon.h
	GameStateInGame.cpp
	GameStateInGame.h
	GameStatePostGame.cpp
	GameStatePostGame.h
	GameStatePreGame.cpp
	GameStatePreGame.h)

set(SOURCES_OTHERS
	Game.cpp
	Game.h
	GameDll.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES_OTHERS} ${SOURCEC_STATES}) 
source_group("src" FILES ${SOURCES_OTHERS})
source_group("src\\states" FILES ${SOURCEC_STATES})

add_dependencies(${PROJECT_NAME} common)
target_link_libraries(${PROJECT_NAME} common)
target_include_directories(${PROJECT_NAME} PUBLIC ${common_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME}
	DESTINATION ${TheLittleInvaders_SOURCE_DIR}/output)

# Compile options (warnings)
#set_warning_level()
#set_warning_as_error()
