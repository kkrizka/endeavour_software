#include <iostream>
#include <iomanip>

#include "UIOCom.h"
#include "EndeavourRaw.h"

int main()
{
  std::cout << "Hello world!" << std::endl;

  std::shared_ptr<DeviceCom> dev=std::make_shared<UIOCom>("/dev/uio2", 0x10000);
  EndeavourRaw end(dev);

  std::cout << "Running reset" << std::endl;
  end.reset();

  return 0;
}
