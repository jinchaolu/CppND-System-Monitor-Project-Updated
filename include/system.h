#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // (Done)TODO: See src/system.cpp
  std::vector<Process>& Processes();  // (Done)TODO: See src/system.cpp
  float MemoryUtilization();          // (Done)TODO: See src/system.cpp
  long UpTime();                      // (Done)TODO: See src/system.cpp
  int TotalProcesses();               // (Done)TODO: See src/system.cpp
  int RunningProcesses();             // (Done)TODO: See src/system.cpp
  std::string Kernel();               // (Done)TODO: See src/system.cpp
  std::string OperatingSystem();      // (Done)TODO: See src/system.cpp

  // (Done)TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif