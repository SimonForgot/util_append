# MAXSDK_INCLUDE_DIR - where the 3dsmax SDK directory containing the headers can be found
# MAXSDK_..._LIBRARY - full path to specified 3dsmax SDK library
# MAXSDK_FOUND       - TRUE if 3dsmax SDK was found

FIND_PATH(MAXSDK_ROOT include/max.h
    ${MAXSDK} $ENV{MAXSDK} $ENV{PATH})
FIND_PATH(MAXSDK_INCLUDE_DIR max.h PATHS ${MAXSDK_ROOT}/include)
FIND_LIBRARY(MAXSDK_core_LIBRARY NAMES core PATHS ${MAXSDK_ROOT}/lib ${MAXSDK_ROOT}/lib/x64/Release)

IF(MAXSDK_INCLUDE_DIR AND MAXSDK_core_LIBRARY)
    file(GLOB MAXSDK_LIBS "${MAXSDK_ROOT}/lib/x64/Release/*.lib")
    SET(MAXSDK_FOUND TRUE)
ELSE()
    SET(MAXSDK_FOUND FALSE)
ENDIF()
