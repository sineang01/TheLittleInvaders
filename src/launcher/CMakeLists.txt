cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project(launcher VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES_ALL main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES_ALL}) 
source_group("src" FILES ${SOURCES_ALL})

add_dependencies(${PROJECT_NAME} common)
target_link_libraries(${PROJECT_NAME} common)
target_include_directories(${PROJECT_NAME} PUBLIC ${common_SOURCE_DIR})

add_dependencies(${PROJECT_NAME} engine)
target_link_libraries(${PROJECT_NAME} engine)

add_dependencies(${PROJECT_NAME} game)
target_link_libraries(${PROJECT_NAME} game)

install(TARGETS ${PROJECT_NAME}
	DESTINATION ${TheLittleInvaders_SOURCE_DIR}/output)

# Compile options (warnings)
#set_warning_level()
#set_warning_as_error()
