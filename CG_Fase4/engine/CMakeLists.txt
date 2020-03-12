cmake_minimum_required (VERSION 2.6)

# Project name
PROJECT(engine)

if (NOT APPLE)
    if (WIN32)
        set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
        include_directories(
                ${TOOLKITS_FOLDER}/glew
                ${TOOLKITS_FOLDER}/glut
                ${TOOLKITS_FOLDER}/devil)
        link_directories(
                ${TOOLKITS_FOLDER}/glew
                ${TOOLKITS_FOLDER}/glut
                ${TOOLKITS_FOLDER}/devil)
    else(WIN32)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif(WIN32)
endif(NOT APPLE)

if (NOT WIN32)
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    find_package(DevIL REQUIRED)
    link_libraries(${IL_LIBRARIES} )
    include_directories(${IL_INCLUDE_DIR})
endif(NOT WIN32)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

set(CMAKE_BUILD_TYPE Release)

# Flags to compile
add_compile_options(-Wall -Wextra -Wpedantic -std=c++11 -O2)
add_executable(${PROJECT_NAME} engine.cpp headers/engine.h tinyxml2.cpp headers/tinyxml2.h parser.cpp headers/parser.h Point.cpp headers/Point.h Transformation.cpp headers/Transformation.h Group.cpp headers/Group.h Camera.cpp headers/Camera.h Shape.cpp headers/Shape.h Light.cpp headers/Light.h Material.cpp headers/Material.h Scene.cpp headers/Scene.h)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glut32 glew32 DevIL)
    file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${TOOLKITS_FOLDER}/devil/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR})

else(WIN32)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif (WIN32)