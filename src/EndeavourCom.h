#ifndef ENDEAVOURCOM_H
#define ENDEAVOURCOM_H

#include <memory>

#include "DeviceCom.h"
#include "EndeavourRaw.h"

class EndeavourCom : public DeviceCom
{
public:
  EndeavourCom(unsigned int amacid, std::shared_ptr<DeviceCom> fpgaCom);

  void reset();

  void setid(unsigned int padid);

  virtual void write_reg(unsigned int address, unsigned int data);
  virtual unsigned int read_reg(unsigned int address);

private:
  unsigned int m_amacid;

  std::unique_ptr<EndeavourRaw> m_raw;
  std::shared_ptr<DeviceCom> m_fpgaCom;

  unsigned int calc_crc(unsigned long long int data) const;
};

#endif //ENDEAVOURCOM_H
