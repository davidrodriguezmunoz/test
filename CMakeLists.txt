# Set minimum required version of CMake
cmake_minimum_required(VERSION 2.8.12)

# Do not allow in-source builds so as to keep source directory clean
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# Create project
# Use legacy syntax to keep compatibility with CMake < 3.0
project("fee" C)
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "")
set(PROJECT_VERSION "1.0")
set(PROJECT_DESCRIPTION "Library to serialized and deserialize fee electronics packets")

# Additional search paths for CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Define GNU standard installation directories
include(GNUInstallDirs)

# Enable compiler warnings
include(cc-warnings)

# Build as a dinamic library by default 
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set output directory for library files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Define source files
set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SRCS
	"${SRCDIR}/common/fee_common.c"
	"${SRCDIR}/PTD/fee_PTD.c"
	"${SRCDIR}/TC/fee_TCWrite.c"
	"${SRCDIR}/TM/fee_TMRead.c"
	"${SRCDIR}/TC/fee_TCRead.c"
	"${SRCDIR}/TM/fee_TMWrite.c"
)

# Add library target
add_library(${PROJECT_NAME} ${SRCS})

# Specify libraries to link
target_link_libraries(${PROJECT_NAME} m)

# Add coverage option
option(COVERAGE_BUILD "Build for coverage analysis" OFF)
if(COVERAGE_BUILD)
	target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
	target_link_options(${PROJECT_NAME} PRIVATE --coverage)
endif()

# Ignore known warnings
set_source_files_properties("${SRCDIR}/TC/fee_TCWrite.c" PROPERTIES COMPILE_FLAGS -Wno-type-limits)

# Set public headers
set(INCDIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(INCS
	"${INCDIR}/fee.h"
)

# Use include directory for building the library and programs that use it
target_include_directories(${PROJECT_NAME} PUBLIC "${INCDIR}")

# Ensure installation of public header and set versions
set_target_properties(${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER "${INCS}"
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
)

# NAMELINK_COMPONENT only available in CMake >= 3.12
if(NOT "${CMAKE_VERSION}" VERSION_LESS "3.12")
	set(LIBRARY_NAMELINK_COMPONENT NAMELINK_COMPONENT Namelinks)
endif()

# Specify rules to run at install time
install(TARGETS ${PROJECT_NAME}
	ARCHIVE
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Libraries
	LIBRARY
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Libraries
		${LIBRARY_NAMELINK_COMPONENT}
	PUBLIC_HEADER
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		COMPONENT Headers
)

# Enable testing with CTest
include(CTest)

# Add test subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
	add_subdirectory("tests")
endif()

# Configure packaging options
include(cpack-config)
