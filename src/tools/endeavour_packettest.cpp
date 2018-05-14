#include <iostream>
#include <iomanip>

#include "UIOCom.h"
#include "EndeavourCom.h"
#include "EndeavourComException.h"

int main()
{
  std::cout << "Hello world!" << std::endl;

  try
    {
      std::shared_ptr<DeviceCom> dev=std::make_shared<UIOCom>("/dev/uio2", 0x10000);
      EndeavourCom end(0x15, dev);

      std::cout << "Running reset" << std::endl;
      end.reset();

      std::cout << "SETID" << std::endl;
      end.setid(0);

      std::cout << "WRITE" << std::endl;
      end.write_reg(1, 1);

      std::cout << "READ" << std::endl;
      unsigned long int read=end.read_reg(1);

      if(read!=1)
	{
	  std::cout << "Read error! 0x" << std::hex << std::setw(8) << std::setfill('0') << read << " != 0x" << std::setw(8) << std::setfill('0') << 1 << std::dec << std::endl;
	}
    }
  catch(EndeavourComException e)
    {
      std::cout << e.what() << std::endl;
    }
  catch(...)
    {
      std::cout << "Unknown (and unhandled) exception" << std::endl;
    }
  return 0;
}
