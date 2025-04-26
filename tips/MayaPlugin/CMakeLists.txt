cmake_minimum_required(VERSION 3.13)
project(spReticleLoc CXX)
# according to
# https://help.autodesk.com/view/MAYAUL/2020/ENU/?guid=__developer_Maya_SDK_MERGED_SettingUpCMake_The_CMakeList_File_html
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

# maya source files
set(MEL_FILES spReticleLoc.mel AEspReticleLocTemplate.mel)
set(SOURCE_FILES GPURenderer.cpp OpenGLRenderer.cpp spReticleLoc.cpp
                 V2Renderer.cpp ${MEL_FILES})
# maya native libs
set(LIBRARIES OpenMayaRender Foundation OpenMayaUI OpenMaya)

# third-party
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
# third-party include
set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
# third-party libs
set(PACKAGE_LIBS ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

build_plugin()
