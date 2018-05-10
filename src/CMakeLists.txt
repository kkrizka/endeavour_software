SET(SrcFiles DeviceCom.cpp
  UIOCom.cpp
  EndeavourRaw.cpp
)

ADD_LIBRARY(endeavour SHARED ${SrcFiles}) 

ADD_SUBDIRECTORY(tools)
