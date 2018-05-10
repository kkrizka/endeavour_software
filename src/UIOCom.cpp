#include "UIOCom.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

UIOCom::UIOCom(const std::string& device, unsigned int size)
  : m_size(size)
{
  m_fd = open(device.c_str(), O_RDWR);
  m_ptr = (unsigned*)mmap(NULL, m_size, PROT_READ|PROT_WRITE, MAP_SHARED, m_fd, 0);
}

UIOCom::~UIOCom()
{
  munmap(m_ptr, m_size);
}


void UIOCom::write_reg(unsigned int address, unsigned int data)
{ m_ptr[address] = data; }

unsigned int UIOCom::read_reg(unsigned int address)
{ return m_ptr[address]; };
