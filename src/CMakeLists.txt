SET(SrcFiles DeviceCom.cpp
  UIOCom.cpp
  EndeavourRaw.cpp
)

ADD_LIBRARY(endeavour SHARED ${SrcFiles}) 
INSTALL(TARGETS endeavour LIBRARY DESTINATION lib)
SET_TARGET_PROPERTIES(endeavour PROPERTIES
  SOVERSION ${endeavour_VERSION_MAJOR}
  VERSION ${endeavour_VERSION_MAJOR}.${endeavour_VERSION_MINOR}
  )


ADD_SUBDIRECTORY(tools)
