find_package(Doxygen REQUIRED)

###############################################################################
# Set up Doxygen
###############################################################################

# Find public headers
get_target_property(BACTRIA_PUBLIC_HEADER_DIR bactria INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE BACTRIA_PUBLIC_HEADERS ${BACTRIA_PUBLIC_HEADER_DIR}/*.hpp)

# Set up Doxygen variables
set(DOXYGEN_INPUT_DIR ${BACTRIA_PUBLIC_HEADER_DIR})
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Configure Doxygen
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Create output directory
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

# Run Doxygen
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${BACTRIA_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating Doxygen documentation"
                   VERBATIM)

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

###############################################################################
# Install docs
###############################################################################
install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
