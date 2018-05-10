INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/lib )

# add executables
FILE(GLOB tools [a-zA-Z]*.c[a-zA-Z]*)

FOREACH(target ${tools})
  GET_FILENAME_COMPONENT(execname ${target} NAME_WE)
  GET_FILENAME_COMPONENT(srcfile ${target} NAME)

  ADD_EXECUTABLE(${execname} ${srcfile})
  TARGET_LINK_LIBRARIES(${execname} -lendeavour)
ENDFOREACH()
