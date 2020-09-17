find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)

###############################################################################
# Set up Doxygen first
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
# Configure Sphinx next
###############################################################################

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
                   COMMAND
                    ${SPHINX_EXECUTABLE} -b html
                    -Dbreathe_projects.bactria=${DOXYGEN_OUTPUT_DIR}/xml
                    ${SPHINX_SOURCE} ${SPHINX_BUILD}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS
                    ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
                    ${CMAKE_CURRENT_SOURCE_DIR}/license.rst
                    ${CMAKE_CURRENT_SOURCE_DIR}/user.rst
                    ${CMAKE_CURRENT_SOURCE_DIR}/user/event.rst
                    ${CMAKE_CURRENT_SOURCE_DIR}/user/phase.rst
                    ${CMAKE_CURRENT_SOURCE_DIR}/user/region.rst
                    ${DOXYGEN_INDEX_FILE}
                   MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
                   COMMENT "Generating Sphinx documentation")

add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})

###############################################################################
# Install Sphinx docs
###############################################################################
# install(DIRECTORY ${SPHINX_BUILD}
#         DESTINATION ${CMAKE_INSTALL_DOCDIR})
