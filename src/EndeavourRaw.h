#ifndef ENDEAVOURRAW_H
#define ENDEAVOURCOM_H

#include <memory>

#include "DeviceCom.h"

class EndeavourRaw
{
public:
  EndeavourRaw(std::shared_ptr<DeviceCom> fpgaCom);

  void reset();

  void sendData(unsigned int data, uint size);

  bool isDataValid();
  void readData(unsigned int& data, uint& size);

private:
  std::shared_ptr<DeviceCom> m_fpgaCom;
};

#endif //ENDEAVOURCOM_H
