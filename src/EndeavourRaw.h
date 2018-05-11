#ifndef ENDEAVOURRAW_H
#define ENDEAVOURCOM_H

#include <memory>

#include "DeviceCom.h"

class EndeavourRaw
{
public:
  EndeavourRaw(std::shared_ptr<DeviceCom> fpgaCom);

  void reset();

  void sendData(unsigned long long int data, unsigned int size);

  bool isDataValid();
  void readData(unsigned long long int& data, unsigned int& size);

private:
  std::shared_ptr<DeviceCom> m_fpgaCom;
};

#endif //ENDEAVOURCOM_H
