#include "EndeavourRaw.h"

EndeavourRaw::EndeavourRaw(std::shared_ptr<DeviceCom> fpgaCom)
  : m_fpgaCom(fpgaCom)
{ }

void EndeavourRaw::reset()
{ m_fpgaCom->write_reg(0, 0x1); }

bool EndeavourRaw::isDataValid()
{
  m_fpgaCom->read_reg(0) & 0x1;
}

void EndeavourRaw::sendData(unsigned int data, uint size)
{
  m_fpgaCom->write_reg(1, size);
  m_fpgaCom->write_reg(2, data);
  m_fpgaCom->write_reg(0, 0x2);
}

void EndeavourRaw::readData(unsigned int& data, uint& size)
{
  if(isDataValid())
    {
      size=m_fpgaCom->read_reg(4);
      data=m_fpgaCom->read_reg(5);
    }
  else
    {
      size=0;
      data=0;
    }
}
