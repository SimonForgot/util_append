# Find NXRENDERER headers and libraries.
#
# This module requires the following variables to be defined:
#
#   NXRENDERER_ROOT           Path to the NXRenderer root directory
#   NXRENDERER_INCLUDE_DIR   Path to the /include directory
#   NXRENDERER_LIBRARY       Path to the nxcore library file
#
# This module defines the following variables:
#
#   NXRENDERER_FOUND         True if NXRenderer was found
#   NXRENDERER_INCLUDE_DIRS  Where to find NXRenderer header files
#   NXRENDERER_LIBRARIES     List of NXRenderer libraries to link against
#

SET( NXRENDER_INCLUDE_DIR NXRENDER_INCLUDE_DIR-NOTFOUND )
FIND_PATH( NXRENDER_INCLUDE_DIR NxAPI.h 
        PATH 
        "${NXRENDERER_ROOT}/include"
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_CMAKE_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_SYSTEM_PATH
        DOC "The directory where NxAPI.h resides" )

SET( NXRENDERER_LIBRARY NXRENDERER_LIBRARY-NOTFOUND )
FIND_LIBRARY( NXRENDERER_LIBRARY nxcore
              PATHS
              "${NXRENDERER_ROOT}/lib/"
              "${NXRENDERER_ROOT}/bin/"
              NO_DEFAULT_PATH
              NO_CMAKE_ENVIRONMENT_PATH
              NO_CMAKE_PATH
              NO_SYSTEM_ENVIRONMENT_PATH
              NO_CMAKE_SYSTEM_PATH
              DOC "The nxcore library" )

IF ( ( ${NXRENDER_INCLUDE_DIR} STREQUAL "NXRENDER_INCLUDE_DIR-NOTFOUND" ) OR
     ( ${NXRENDERER_LIBRARY} STREQUAL "NXRENDERER_LIBRARY-NOTFOUND" ) )
  MESSAGE( STATUS "NXRENDERER not found" )
  SET( NXRENDERER_FOUND FALSE )
ELSE()
  MESSAGE( STATUS "NXRENDERER INCLUDE PATH: ${NXRENDER_INCLUDE_DIR}" )
  MESSAGE( STATUS "libnxcore: ${NXRENDERER_LIBRARY}" )
  SET( NXRENDERER_FOUND TRUE )
  INCLUDE_DIRECTORIES( ${NXRENDER_INCLUDE_DIR} )
ENDIF()        

IF( NOT ${NXRENDERER_FOUND} )
    MESSAGE( FATAL_ERROR "NXRenderer is not found (╯°Д°）╯︵ / set \"NXRENDERER_ROOT\" plz." )
ENDIF()
