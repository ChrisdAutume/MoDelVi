
######
# This is the find-script for your project/library used by CMake if this project/libary is to be
# included in another project/library.
######

#
# Renaming MODELVI... -> <PROJECT_NAME>...
#
# MODELVI_DIR -> <PROJECT_NAME>_DIR
# MODELVI_FOUND -> <PROJECT_NAME>_FOUND
# MODELVI_LIBRARIES -> <PROJECT_NAME>_LIBRARIES
# MODELVI_INCLUDES -> <PROJECT_NAME>_INCLUDES

# MODELVI_FIBLIB_LIBRARY -> <PROJECT_NAME>_<...>_LIBRARY
# MODELVI_FIBLIB_LIBRARY_RELEASE -> <PROJECT_NAME>_<...>_LIBRARY_RELEASE
# MODELVI_FIBLIB_LIBRARY_DEBUG -> <PROJECT_NAME>_<...>_LIBRARY_DEBUG
# MODELVI_FIBLIB_INCLUDE_DIR -> <PROJECT_NAME>_<...>_INCLUDE_DIR

set(MODELVI_INCLUDES "")
set(MODELVI_LIBRARIES "")

# Definition of function "find" with two mandatory arguments, "LIB_NAME" and "HEADER".
macro (find LIB_NAME HEADER)

    set(HINT_PATHS ${ARGN})

    if (${LIB_NAME} STREQUAL "modelvi")
        set(LIB_NAME_UPPER MODELVI)
        set(LIBNAME modelvi)
    else()
        string(TOUPPER MODELVI_${LIB_NAME} LIB_NAME_UPPER)
        set(LIBNAME ${LIB_NAME})
    endif()

    find_path(
	${LIB_NAME_UPPER}_INCLUDE_DIR
	${HEADER}
        ${ENV_MODELVI_DIR}/include
        ${ENV_MODELVI_DIR}/source/${LIB_NAME}/include
        ${MODELVI_DIR}/include
        ${MODELVI_DIR}/source/${LIB_NAME}/include
        ${ENV_PROGRAMFILES}/modelvi/include
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where ${HEADER} resides"
    )


    find_library(
	${LIB_NAME_UPPER}_LIBRARY_RELEASE
        NAMES ${LIBNAME}
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} library"
    )
    find_library(
	${LIB_NAME_UPPER}_LIBRARY_DEBUG
        NAMES ${LIBNAME}d
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} debug library"
    )
    

    if(${LIB_NAME_UPPER}_LIBRARY_RELEASE AND ${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY "optimized" ${${LIB_NAME_UPPER}_LIBRARY_RELEASE} "debug" ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    elseif(${LIB_NAME_UPPER}_LIBRARY_RELEASE)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_RELEASE})
    elseif(${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    endif()

    list(APPEND MODELVI_INCLUDES ${${LIB_NAME_UPPER}_INCLUDE_DIR})
    list(APPEND MODELVI_LIBRARIES ${${LIB_NAME_UPPER}_LIBRARY})

    # DEBUG MESSAGES
    # message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")
    # message("${LIB_NAME_UPPER}_LIBRARY_RELEASE = ${${LIB_NAME_UPPER}_LIBRARY_RELEASE}")
    # message("${LIB_NAME_UPPER}_LIBRARY_DEBUG   = ${${LIB_NAME_UPPER}_LIBRARY_DEBUG}")
    # message("${LIB_NAME_UPPER}_LIBRARY         = ${${LIB_NAME_UPPER}_LIBRARY}")

endmacro(find)


# load standard CMake arguments (c.f. http://stackoverflow.com/questions/7005782/cmake-include-findpackagehandlestandardargs-cmake)
include(FindPackageHandleStandardArgs)

if(CMAKE_CURRENT_LIST_FILE)
    get_filename_component(MODELVI_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif()

file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" ENV_PROGRAMFILES)
file(TO_CMAKE_PATH "$ENV{MODELVI_DIR}" ENV_MODELVI_DIR)

set(LIB_PATHS
    ${MODELVI_DIR}/build
    ${MODELVI_DIR}/build/Release
    ${MODELVI_DIR}/build/Debug
    ${MODELVI_DIR}/build-release
    ${MODELVI_DIR}/build-debug
    ${MODELVI_DIR}/lib
    ${ENV_MODELVI_DIR}/lib
    ${ENV_PROGRAMFILES}/modelvi/lib
    /usr/lib
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    /usr/lib64
    /usr/local/lib64
    /sw/lib64
    /opt/local/lib64
)

# Find libraries
find(fiblib fiblib/fiblib_api.h ${LIB_PATHS})

if(MODELVI_FIBLIB_LIBRARY)
  # add dependencies
endif()


# DEBUG
# message("MODELVI_INCLUDES  = ${MODELVI_INCLUDES}")
# message("MODELVI_LIBRARIES = ${MODELVI_LIBRARIES}")

find_package_handle_standard_args(MODELVI DEFAULT_MSG MODELVI_LIBRARIES MODELVI_INCLUDES)
mark_as_advanced(MODELVI_FOUND)
