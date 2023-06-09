cmake_minimum_required (VERSION 3.25)

project(TargetAccessPluginClientExamples CXX)

if (NOT DEFINED TOOLKIT_DIR)
  message(FATAL_ERROR "You must configure with -DTOOLKIT_DIR=\"C:/path/to/Embedded/Workbench/x.xx/arm\"")
endif()
find_library(TAC_Lib
             NAMES TargetAccessClientSDK 
             PATHS "${TOOLKIT_DIR}/src/TargetAccessPlugin/lib"
             REQUIRED)

if(MSVC)
  add_executable(mem-reader mem-reader.cpp)
  add_executable(mem-writer mem-writer.cpp)
  add_executable(itm-logger itm-logger.cpp)
  set_target_properties(
    mem-reader
    mem-writer
    itm-logger
    PROPERTIES
      INCLUDE_DIRECTORIES "${TOOLKIT_DIR}/src/TargetAccessPlugin/inc"
      COMPILE_OPTIONS /Zi
      LINK_OPTIONS /SUBSYSTEM:console
      LINK_LIBRARIES ${TAC_Lib} )
  add_custom_command(TARGET itm-logger POST_BUILD 
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                     "${TOOLKIT_DIR}/../common/bin/TargetAccessClientSDK.dll"
                     $<TARGET_FILE_DIR:itm-logger>)
endif()




