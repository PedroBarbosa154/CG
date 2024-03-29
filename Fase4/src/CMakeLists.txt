cmake_minimum_required(VERSION 3.5)

# Project Name - Generator
PROJECT(generator)
add_executable(${PROJECT_NAME} Generator/generator.cpp
								Generator/primitives.cpp
								utils/ponto.cpp
								utils/float_vector.cpp)

# Project Name - Engine
PROJECT(engine)
add_executable(${PROJECT_NAME} Engine/engine.cpp
								Engine/utils/group.cpp
								Engine/utils/fpsCamera.cpp
								Engine/utils/staticCamera.cpp
								Engine/utils/parser.cpp
								Engine/utils/lights.cpp
								Engine/utils/model.cpp
								lib/tinyxml2.cpp
								utils/ponto.cpp
								utils/float_vector.cpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_BUILD_TYPE Debug)
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif (NOT OPENGL_FOUND)

if (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")

	if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
		message(ERROR ": GLEW not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")	

	if (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")
		message(ERROR ": DevIL not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")	

	include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
										  ${TOOLKITS_FOLDER}/glut/glut32.lib
										  ${TOOLKITS_FOLDER}/glew/glew32.lib
										  ${TOOLKITS_FOLDER}/devil/devIL.lib)

	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll" AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/devil/devil.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll" AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	find_package(DevIL REQUIRED)
	link_libraries(${IL_LIBRARIES})
	include_directories(${IL_INCLUDE_DIR})

	if (NOT APPLE)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
		target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
	else (NOT APPLE)
		target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${IL_LIBRARIES})
	endif (NOT APPLE)

	if (NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif (NOT GLUT_FOUND)

endif(WIN32)

file(COPY ${CMAKE_SOURCE_DIR}/../textures/stars.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/sun.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/mercury.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/venus.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/earth.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/moon.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/mars.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/asteroid_belt.png DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/jupiter.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/io.png DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/europa.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/ganymede.png DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/callisto.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/saturn.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/saturn_ring.png DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/uranus.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_SOURCE_DIR}/../textures/neptune.jpg DESTINATION ${CMAKE_BINARY_DIR}/images)
