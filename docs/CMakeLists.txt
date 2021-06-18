include(FetchContent)

find_package(Doxygen REQUIRED)

###############################################################################
# Set up Doxygen
###############################################################################

# Better stylesheet
FetchContent_Declare(awesome_theme
                     GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
                     GIT_TAG v1.4.0)
FetchContent_MakeAvailable(awesome_theme)

# Find public headers
get_target_property(BACTRIA_PUBLIC_HEADER_DIR bactria INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE BACTRIA_PUBLIC_HEADERS ${BACTRIA_PUBLIC_HEADER_DIR}/*.hpp)

set(DOXYGEN_EXAMPLE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples)
set(DOXYGEN_HTML_EXTRA_STYLESHEET ${awesome_theme_SOURCE_DIR}/doxygen-awesome.css custom.css)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_GENERATE_XML NO)
set(DOXYGEN_HIDE_SCOPE_NAMES NO)
set(DOXYGEN_SHOW_NAMESPACES YES)


doxygen_add_docs(bactriaDocs ${BACTRIA_PUBLIC_HEADERS} ALL COMMENT "Generating Doxygen documentation")

###############################################################################
# Install docs
###############################################################################
install(DIRECTORY ${DOXYGEN_OUTPUT_DIRECTORY}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
