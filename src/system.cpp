#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// (Done)TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// (Done)TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  // Collect PIDs from previous processes
  set<int> prevPIDs;
  for (Process proces : this -> processes_) {
    prevPIDs.insert(proces.Pid());
  }
  
  // Add new PIDs from current processes
  vector<int> pids = LinuxParser::Pids();
  for (int pid : pids) {
    if (prevPIDs.count(pid) == 0) {
      (this -> processes_).emplace_back(pid);
    }
  }
  
  std::sort((this -> processes_).begin(), (this -> processes_).end(), std::greater<Process>());
  
  return (this -> processes_);
}

// (Done)TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// (Done)TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// (Done)TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// (Done)TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// (Done)TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// (Done)TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }