#ifndef DEVICECOM_H
#define DEVICECOM_H

class DeviceCom
{
public:
  DeviceCom();

  virtual void write_reg(unsigned int address, unsigned int data) =0;
  virtual unsigned int read_reg(unsigned int address) =0;
};

#endif // DEVICECOM_H
