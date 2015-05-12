
# Generate meta-header
configure_file(modelvi-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/modelvi-version.h)

# We do NOT want to deploy this header (at least not for binary packages)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/template/template-version.h DESTINATION ${INSTALL_INCLUDE}/template)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Libraries
set(IDE_FOLDER "")
add_subdirectory(modelvilib)

# Applications
set(IDE_FOLDER "Applications")
add_subdirectory(fibcmd)
add_subdirectory(iCubVision)

