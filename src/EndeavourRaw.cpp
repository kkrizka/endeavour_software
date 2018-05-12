#include "EndeavourRaw.h"

EndeavourRaw::EndeavourRaw(std::shared_ptr<DeviceCom> fpgaCom)
  : m_fpgaCom(fpgaCom)
{ }

void EndeavourRaw::reset()
{ m_fpgaCom->write_reg(0, 0x1); }

bool EndeavourRaw::isDataValid()
{
  return (m_fpgaCom->read_reg(0)>>1)&1;
}

void EndeavourRaw::sendData(unsigned long long int data, unsigned int size)
{
  m_fpgaCom->write_reg(1, size);
  m_fpgaCom->write_reg(2, (data>>0 )&0xFFFFFFFF);
  m_fpgaCom->write_reg(3, (data>>32)&0xFFFFFFFF);
  m_fpgaCom->write_reg(0, 0x2);
}

void EndeavourRaw::readData(unsigned long long int& data, unsigned int& size)
{
  if(isDataValid())
    {
      size=m_fpgaCom->read_reg(4);
      data=m_fpgaCom->read_reg(6);
      data<<=32;
      data|=m_fpgaCom->read_reg(5);
    }
  else
    {
      size=0;
      data=0;
    }
}
