CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(YARP REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/modelvilib/include
	${YARP_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS} 
)

FILE(GLOB folder_source 
	modelvilib/source/*.cpp
)
FILE(GLOB folder_header
	modelvilib/include/*.h
)

set(libs
    ${YARP_LIBRARIES} 
    ${OpenCV_LIBS}
)

SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})

LINK_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/modelvilib/build
)

# Set up modelvi library
ADD_LIBRARY(modelvilib SHARED ${folder_source} ${folder_header})
TARGET_LINK_LIBRARIES(modelvilib ${YARP_LIBRARIES} ${OpenCV_LIBS})


ADD_EXECUTABLE(iCubVision ${PROJECT_SOURCE_DIR}/iCubVision/main.cpp)
ADD_EXECUTABLE(fibcmd ${PROJECT_SOURCE_DIR}/fibcmd/main.cpp)

TARGET_LINK_LIBRARIES(iCubVision ${YARP_LIBRARIES} modelvilib)
TARGET_LINK_LIBRARIES(fibcmd ${YARP_LIBRARIES} modelvilib)
