#include <unistd.h>

#include <iostream>
#include <iomanip>

#include "UIOCom.h"
#include "EndeavourCom.h"
#include "EndeavourComException.h"

void print_help()
{
  std::cout << "usage: endeavour [driver options] command [command parameters]" << std::endl;
  std::cout << std::endl;
  std::cout << "driver options" << std::endl;
  std::cout << " -d device: device to use for UIO communication (default: /dev/uio2)" << std::endl;
  std::cout << " -a amacid: amacid to use for communication (default: 0x15)" << std::endl;
  std::cout << std::endl;
  std::cout << "commands" << std::endl;
  std::cout << " reset: reset the Endeavour master firmware" << std::endl;
  std::cout << " setid idpads/efuse internalid: set amacid for internalid efuse or idpads" << std::endl;
  std::cout << " write address data: write data to address " << std::endl;
  std::cout << " read address: read address " << std::endl;
}

int main(int argc, char* argv[])
{
  std::string device="/dev/uio2";
  unsigned short int amacid=0x15;

  // Parse options
  int opt;
  while( (opt = getopt(argc, argv, "d:a:")) != -1 )
    {
      switch( opt )
	{
	case 'd':
	  device=optarg;
	  break;
	case 'a':
	  amacid=std::stoul(optarg, nullptr, 0);
	  break;
	case '?':  // unknown option...
	  print_help();
	  return 1;
	  break;
	}
    }

  // Create the communication object
  std::shared_ptr<DeviceCom> dev=std::make_shared<UIOCom>(device, 0x10000);
  EndeavourCom end(amacid, dev);

  // Determine the command
  if(argc<=optind)
    {
      print_help();
      return 1;
    }

  std::string command=argv[optind];

  // Run the commands
  try
    {
      if(command=="reset")
	{
	  end.reset();
	}
      else if(command=="setid")
	{
	  // Need two more
	  if(argc<=(optind+2))
	    {
	      print_help();
	      return 1;
	    }

	  EndeavourCom::REFMODE refmode=(argv[optind+1]=="idpads")?EndeavourCom::REFMODE::IDPads:EndeavourCom::REFMODE::EfuseId;
	  unsigned int refid=std::stoul(argv[optind+2], nullptr, 0);

	  end.setid(refmode,refid);
	}
      else if(command=="write")
	{
	  // Need two more
	  if(argc<=(optind+2))
	    {
	      print_help();
	      return 1;
	    }

	  unsigned int address=std::stoul(argv[optind+1], nullptr, 0);
	  unsigned int data=std::stoul(argv[optind+2], nullptr, 0);

	  end.write_reg(address,data);
	}
      else if(command=="read")
	{
	  // Need one more
	  if(argc<=(optind+1))
	    {
	      print_help();
	      return 1;
	    }

	  unsigned int address=std::stoul(argv[optind+1], nullptr, 0);

	  unsigned int read=end.read_reg(address);
	  std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << read << std::endl;
	}
    }
  catch(EndeavourComException e)
    {
      std::cout << e.what() << std::endl;
    }

  return 0;
}
