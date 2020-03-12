cmake_minimum_required (VERSION 2.6)

# Project name
PROJECT(engine)

# GLEW LIB
# ------------------------------------
if (NOT APPLE)
    if (WIN32)
        set(GLEW_ROOT_FOLDER "" CACHE PATH "Path to GLEW folder")
        include_directories(${GLEW_ROOT_FOLDER})
        link_directories(${GLEW_ROOT_FOLDER})
    else(WIN32)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif(WIN32)
endif(NOT APPLE)
# ------------------------------------

# GLUT LIB
# ------------------------------------
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
# ------------------------------------

# OPEN GL LIB
# ------------------------------------
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
# ------------------------------------

set(CMAKE_BUILD_TYPE Release)

# Flags to compile
add_compile_options(-Wall -Wextra -Wpedantic -std=c++11 -O2)
add_executable(${PROJECT_NAME} engine.cpp headers/engine.h tinyxml2.cpp headers/tinyxml2.h parser.cpp headers/parser.h Point.cpp headers/Point.h Transformation.cpp headers/Transformation.h Group.cpp headers/Group.h Camera.cpp headers/Camera.h Shape.cpp headers/Shape.h)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

