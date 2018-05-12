#include <iostream>
#include <iomanip>

#include "UIOCom.h"
#include "EndeavourCom.h"

int main()
{
  std::cout << "Hello world!" << std::endl;

  std::shared_ptr<DeviceCom> dev=std::make_shared<UIOCom>("/dev/uio2", 0x10000);
  EndeavourCom end(0x15, dev);

  std::cout << "Running reset" << std::endl;
  end.reset();

  std::cout << "SETID" << std::endl;
  end.setid(0);

  std::cout << "WRITE" << std::endl;
  end.write_reg(1, 1);

  std::cout << "READ" << std::endl;
  end.read_reg(1);

  return 0;
}
