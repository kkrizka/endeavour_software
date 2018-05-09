#include <iostream>

#include "UIOCom.h"

int main()
{
  std::cout << "Hello world!" << std::endl;

  UIOCom com("/dev/uio2", 0x10000);

  std::cout << "Running reset" << std::endl;
  com.write_reg(0, 0x1);

  std::cout << "Writing data" << std::endl;
  com.write_reg(1, 0x8);
  com.write_reg(2, 0xFF);
  std::cout << "nbitsin = " << com.read_reg(1) << std::endl;
  std::cout << "datain = 0x" << std::hex << com.read_reg(2) << std::dec << std::endl;

  std::cout << "Reading data" << std::endl;
  std::cout << "nbitsout = " << com.read_reg(4) << std::endl;
  std::cout << "dataout = 0x" << std::hex << com.read_reg(5) << std::dec << std::endl;

  std::cout << "Sending data" << std::endl;
  com.write_reg(0, 2);

  std::cout << "Reading data" << std::endl;
  std::cout << "nbitsout = " << com.read_reg(4) << std::endl;
  std::cout << "dataout = 0x" << std::hex << com.read_reg(5) << std::dec << std::endl;

  return 0;
}
