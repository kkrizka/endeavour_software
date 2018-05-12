#include "EndeavourCom.h"

#include <iostream>
#include <unistd.h>

EndeavourCom::EndeavourCom(unsigned int amacid, std::shared_ptr<DeviceCom> fpgaCom)
  : m_amacid(amacid&0x1F), m_fpgaCom(fpgaCom)
{
  m_raw=std::unique_ptr<EndeavourRaw>(new EndeavourRaw(m_fpgaCom));
}

void EndeavourCom::reset()
{
  m_raw->reset();
}

void EndeavourCom::setid(unsigned int padid)
{
  unsigned long long int databits=0;

  //{3’b110, 5’b11111, 3’b111, newamacid[4:0], 4’b1111, efuseid[19:0], 3’b111, idpads[4:0], crc[7:0]}

  // SETID - 3'b110
  databits<<=3;
  databits|=0b110; 

  // 3'b11111
  databits<<=5;
  databits|=0b11111;

  // 3'b111
  databits<<=3;
  databits|=0b111;

  // newamacid[4:0]
  databits<<=5;
  databits|=(m_amacid&0x1F);

  // 4'b1111
  databits<<=4;
  databits|=0b1111;

  // efuseid[19:0]
  databits<<=20;
  databits|=0xFFFFF;

  // 3'b111
  databits<<=3;
  databits|=0b111;

  // idpads[4:0]
  databits<<=5;
  databits|=(padid&0x1F);

  // crc[7:0]
  unsigned int crc=calc_crc(databits);
  databits<<=8;
  databits|=(crc&0xFF);

  // send data
  m_raw->sendData(databits, 56);

  // wait for response ( poll :( )
  while(!m_raw->isDataValid()) { continue; }

  unsigned long long int read_data;
  unsigned int read_nbits;
  m_raw->readData(read_data,read_nbits);
  std::cout << m_raw->isDataValid() << " " << read_nbits << " " << std::hex << read_data << std::dec << std::endl;
}

void EndeavourCom::write_reg(unsigned int address, unsigned int data)
{
  unsigned long long int databits=0;

  //{3’b111, amacid[4:0], addr[7:0], data[31:0], crc[7:0]}

  // WRITE - 3'b110
  databits<<=3;
  databits|=0b111; 

  // amacid[4:0]
  databits<<=5;
  databits|=(m_amacid&0x1F);

  // addr[7:0]
  databits<<=8;
  databits|=(address&0xFF);

  // data[31:0]
  databits<<=32;
  databits|=(data&0xFFFFFFFF);

  // crc[7:0]
  unsigned int crc=calc_crc(databits);
  databits<<=8;
  databits|=(crc&0xFF);

  // send data
  m_raw->sendData(databits, 56);

  // wait for response ( poll :( )
  while(!m_raw->isDataValid()) { continue; }

  unsigned long long int read_data;
  unsigned int read_nbits;
  m_raw->readData(read_data,read_nbits);
  std::cout << m_raw->isDataValid() << " " << read_nbits << " " << std::hex << read_data << std::dec << std::endl;
}

unsigned int EndeavourCom::read_reg(unsigned int address)
{
  unsigned long long int databits=0;

  //{3’b101, amacid[4:0], addr[7:0]}

  // READ - 3'b101
  databits<<=3;
  databits|=0b101;

  // amacid[4:0]
  databits<<=5;
  databits|=(m_amacid&0x1F);

  // addr[7:0]
  databits<<=8;
  databits|=(address&0xFF);

  // send data
  m_raw->sendData(databits, 16);

  // wait for response ( poll :( )
  while(!m_raw->isDataValid()) { continue; }

  unsigned long long int read_data;
  unsigned int read_nbits;
  m_raw->readData(read_data,read_nbits);
  std::cout << m_raw->isDataValid() << " " << read_nbits << " " << std::hex << read_data << std::dec << std::endl;
}

unsigned int EndeavourCom::calc_crc(unsigned long long int data) const
{
  unsigned crc=0;
  for(unsigned int i=0;i<8;i++)
    {
      crc|=(( ((data>>(8*0+i))&1) ^
	      ((data>>(8*1+i))&1) ^
	      ((data>>(8*2+i))&1) ^
	      ((data>>(8*3+i))&1) ^
	      ((data>>(8*4+i))&1) ^
	      ((data>>(8*5+i))&1) )<<i);
    }

  return crc;
}
