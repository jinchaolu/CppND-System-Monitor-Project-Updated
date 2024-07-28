#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor
Process::Process(int pid) : pid_(pid) {}

// (Done)TODO: Return this process's ID
int Process::Pid() { return (this -> pid_); }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    // Read the latest active time and idle time
  this -> cpuTime_ = LinuxParser::CpuUtilization(this -> pid_);
  long currActiveTime = LinuxParser::ActiveJiffies(this -> cpuTime_);
  long currIdleTime = LinuxParser::IdleJiffies(this -> cpuTime_);
  
  // Calculate the utilization between previous and current time
  long activeTime = currActiveTime - (this -> prevActiveTime_);
  long idleTime = currIdleTime - (this -> prevIdleTime_);
  long totalTime = activeTime + idleTime;
  this -> cpuUtilization_ = float(activeTime) / float(totalTime);
  
  // Save the active time and idle time
  this -> prevActiveTime_ = currActiveTime;
  this -> prevIdleTime_ = currIdleTime;
  
  return (this -> cpuUtilization_);
}

// (Done)TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this -> pid_); }

// (Done)TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this -> pid_); }

// (Done)TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this -> pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// (Done)TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return ((this -> cpuUtilization_) < a.cpuUtilization_);
}