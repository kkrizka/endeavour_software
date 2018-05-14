#ifndef ENDEAVOURCOM_H
#define ENDEAVOURCOM_H

#include <memory>

#include "DeviceCom.h"
#include "EndeavourRaw.h"

class EndeavourCom : public DeviceCom
{
public:
  enum REFMODE {IDPads, EfuseId};

  EndeavourCom(unsigned short amacid, std::shared_ptr<DeviceCom> fpgaCom);

  void enableSeqNum(bool enableSeqNum);

  void reset();

  void setid(REFMODE mode, unsigned int refid);

  virtual void write_reg(unsigned int address, unsigned int data);
  virtual unsigned int read_reg(unsigned int address);

private:
  unsigned short m_amacid;

  bool m_enableSeqNum =false;
  unsigned short m_seqnum =0;

  std::unique_ptr<EndeavourRaw> m_raw;
  std::shared_ptr<DeviceCom> m_fpgaCom;

  unsigned int calc_crc(unsigned long long int data) const;
};

#endif //ENDEAVOURCOM_H
