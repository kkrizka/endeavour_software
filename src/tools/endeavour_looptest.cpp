#include <iostream>

#include "UIOCom.h"
#include "EndeavourRaw.h"

int main()
{
  std::cout << "Hello world!" << std::endl;

  std::shared_ptr<DeviceCom> dev=std::make_shared<UIOCom>("/dev/uio2", 0x10000);
  EndeavourRaw end(dev);

  std::cout << "Running reset" << std::endl;
  end.reset();

  std::cout << "Writing data" << std::endl;
  end.sendData(0xFFFF, 8);
  std::cout << " nbitsin = " << dev->read_reg(1) << std::endl;
  std::cout << " datain = 0x" << std::hex << dev->read_reg(2) << std::dec << std::endl;

  std::cout << "Reading data" << std::endl;
  if(end.isDataValid())
    {
      unsigned int data=0, size=0;
      end.readData(data,size);
      std::cout << " nbitsout = " << size << std::endl;
      std::cout << " dataout = 0x" << std::hex << data << std::dec << std::endl;
    }
  else
    std::cout << " No valid data!" << std::endl;

  return 0;
}
