#ifndef FPGACOM_H
#define FPGACOM_H

class FPGACom
{
public:
  FPGACom();

  virtual void write_reg(unsigned int address, unsigned int data) =0;
  virtual unsigned int read_reg(unsigned int address) =0;
};

#endif // FPGACOM_H
