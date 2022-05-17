# Find XXX headers and libraries.
#
# This module requires the following variables to be defined:
#
# XXX_ROOT           Path to the XXX root directory
#
# This module defines the following variables:
#
# XXX_FOUND         True if XXX was found XXX_INCLUDE_DIR  Where to find XXX
# header files XXX_LIBRARIY     List of XXX libraries to link against
#

find_path(
  XXX_INCLUDE_DIR XXX.h
  PATHS "${XXX_ROOT}/include"
  NO_DEFAULT_PATH
  DOC "The directory where XXX.h resides")

find_library(
  XXX_LIBRARY XXX
  PATHS "${XXX_ROOT}/lib/"
  NO_DEFAULT_PATH
  DOC "The XXX library")

if((${XXX_INCLUDE_DIR} STREQUAL "XXX_INCLUDE_DIR-NOTFOUND")
  OR(${XXX_LIBRARY} STREQUAL "XXX_LIBRARY-NOTFOUND"))
  message(STATUS "XXX not found")
  set(XXX_FOUND FALSE)
else()
  message(STATUS "XXX_INCLUDE_DIR: ${XXX_INCLUDE_DIR}")
  message(STATUS "XXX_LIBRARY: ${XXX_LIBRARY}")
  set(XXX_FOUND TRUE)
endif()

if(NOT ${XXX_FOUND})
  message(FATAL_ERROR "XXX is not found (╯°Д°）╯︵ / set \"XXX_ROOT\" plz.")
endif()