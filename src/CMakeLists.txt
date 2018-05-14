SET(SrcFiles DeviceCom.cpp
  UIOCom.cpp
  EndeavourCom.cpp
  EndeavourRaw.cpp

  ComIOException.cpp
  EndeavourComException.cpp
)

ADD_LIBRARY(devcom SHARED ${SrcFiles}) 
INSTALL(TARGETS devcom LIBRARY DESTINATION lib)
SET_TARGET_PROPERTIES(devcom PROPERTIES
  SOVERSION ${endeavour_VERSION_MAJOR}
  VERSION ${endeavour_VERSION_MAJOR}.${endeavour_VERSION_MINOR}
  )


ADD_SUBDIRECTORY(tools)
