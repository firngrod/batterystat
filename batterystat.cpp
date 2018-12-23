#include <stdio.h>
#include <cstdlib>
#include "firnlibs/string/string.hpp"
#include "firnlibs/files/files.hpp"

int main()
{
  // Get the data.
  std::vector<unsigned char> batCapVec, batStatVec;
  FirnLibs::Files::ErrorCode rc = FirnLibs::Files::ReadFile(batCapVec, "/sys/class/power_supply/BAT0/capacity");
  if(rc != FirnLibs::Files::ErrorCode::None)
    return 1;
  rc = FirnLibs::Files::ReadFile(batStatVec, "/sys/class/power_supply/BAT0/status");
  if(rc != FirnLibs::Files::ErrorCode::None)
    return 1;
  //FirnLibs::Files::ReadFile(batCapVec, "capacity");
  //FirnLibs::Files::ReadFile(batStatVec, "status");
  batCapVec.push_back(0);
  batStatVec.push_back(0);
  std::string statStr((char *)&batStatVec[0]);
  std::string capStr((char *)&batCapVec[0]);

  // For proper linewrapping in the terminal afterwards.
  const char escStart[] = "\001";
  const char escEnd[] = "\002";

  // Color based on capacity left
  int capInt = std::stoi(capStr);
  int capInt255 = (int)(capInt / 100.0 * 255);
  printf(escStart);
  printf("\033[38;2;%d;%d;%d;1", 255 - capInt255, capInt255, std::min(255, 256 - 2*abs(capInt255 - 127)));
  // Blinky if <= 10%
  if(capInt < 11)
  {
    printf(";5");
  }
  printf("m");
  printf(escEnd);

  // Print the actual capacity
  printf(capStr.c_str());

  // Charging state
  if(statStr == "Discharging")
  {
    printf(escStart);
    printf("\033[31;1m");
    printf(escEnd);
    printf("--");
  }
  if(statStr == "Charging")
  {
    printf(escStart);
    printf("\033[32;1m");
    printf(escEnd);
    printf("++");
  }
  if(statStr == "Full")
  {
    printf(escStart);
    printf("\033[34;1m");
    printf(escEnd);
    printf("==");
  }

  
  printf(escStart);
  printf("\033[0m");
  printf(escEnd);

  return 0;
}
