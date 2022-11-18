# Include any runtime libraries that are needed by the project for the current platform
include(InstallRequiredSystemLibraries)

# Set package directory
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/pkg")

# Strip all files
set(CPACK_STRIP_FILES YES)

# Package version and description are set automatically if the
# information was passed when calling project(). However, this
# is only supported by CMake >= 3.0.
set(CPACK_PACKAGE_NAME "lib${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_CONTACT "David Rodriguez-Muñoz <david.rodriguez@iac.es>")

# Configure component packaging
set(CPACK_COMPONENTS_ALL Libraries Namelinks Headers)
set(CPACK_COMPONENT_HEADERS_GROUP Development)
set(CPACK_COMPONENT_HEADERS_DEPENDS Libraries)
set(CPACK_COMPONENT_NAMELINKS_GROUP Development)
set(CPACK_COMPONENT_NAMELINKS_DEPENDS Libraries)
set(CPACK_COMPONENT_DEVELOPMENT_DEPENDS Libraries)
set(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Development files")

# Set Debian-specific options
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

# Set Debian-specific options for "libraries" component
set(CPACK_DEBIAN_LIBRARIES_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_DEBIAN_LIBRARIES_PACKAGE_SECTION "libs")
if(NOT ${CMAKE_VERSION} VERSION_LESS "3.6")
	set(CPACK_DEBIAN_LIBRARIES_FILE_NAME DEB-DEFAULT)
endif()

# Set Debian-specific options for "development" group
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_NAME "${CPACK_PACKAGE_NAME}-dev")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_SECTION "libdevel")
if(NOT ${CMAKE_VERSION} VERSION_LESS "3.6")
	set(CPACK_DEBIAN_DEVELOPMENT_FILE_NAME DEB-DEFAULT)
endif()

# Configure installer
include(CPack)
