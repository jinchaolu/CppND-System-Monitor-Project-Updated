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
using std::stof;

// Constructor
Process::Process(int pid) : pid_(pid) {}

// (Done)TODO: Return this process's ID
int Process::Pid() { return (this -> pid_); }

// (Done)TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    // Read the latest active time and idle time
  this -> cpuTime_ = LinuxParser::CpuUtilization(this -> pid_);
  
//   string sUtime = (this -> cpuTime_)[ProcessStates::kUtime_];
//   string sStime = (this -> cpuTime_)[ProcessStates::kStime_];
//   string sCutime = (this -> cpuTime_)[ProcessStates::kCutime_];
//   string sCstime = (this -> cpuTime_)[ProcessStates::kCstime_];
//   string sStarttime = (this -> cpuTime_)[ProcessStates::kStarttime_];
  string sUtime = (this -> cpuTime_)[13];
  string sStime = (this -> cpuTime_)[14];
  string sCutime = (this -> cpuTime_)[15];
  string sCstime = (this -> cpuTime_)[16];
  string sStarttime = (this -> cpuTime_)[21];
  
  float totalTime = stof(sUtime) + stof(sStime) + stof(sCutime) + stof(sCstime);
  float hertz = sysconf(_SC_CLK_TCK);
  float upTime = float(LinuxParser::UpTime());
  float seconds = upTime - (stof(sStarttime) / hertz);
  this -> cpuUtilization_ = ((totalTime / hertz) / seconds);
  
  return (this -> cpuUtilization_);
}

// (Done)TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this -> pid_); }

// (Done)TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this -> pid_); }

// (Done)TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this -> pid_); }

// (Done)TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this -> pid_); }

// (Done)TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return ((this -> cpuUtilization_) < a.cpuUtilization_);
}

bool Process::operator>(Process const& a) const {
  return ((this -> cpuUtilization_) > a.cpuUtilization_);
}