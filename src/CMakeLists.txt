SET(SrcFiles DeviceCom.cpp
  UIOCom.cpp
  EndeavourRaw.cpp
)

ADD_LIBRARY(endeavour SHARED ${SrcFiles}) 
INSTALL(TARGETS endeavour LIBRARY DESTINATION lib)

ADD_SUBDIRECTORY(tools)
