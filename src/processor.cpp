#include <string>
#include <vector>
#include <iostream>
#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::vector;

// (Done)TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  // Read the latest active time and idle time
  this -> cpuTime_ = LinuxParser::CpuUtilization();
  long currActiveTime = LinuxParser::ActiveJiffies(this -> cpuTime_);
  long currIdleTime = LinuxParser::IdleJiffies(this -> cpuTime_);
  
  // Calculate the utilization between previous and current time
  float ans = 0.0;
  long activeTime = currActiveTime - this -> prevActiveTime;
  long idleTime = currIdleTime - this -> prevIdleTime;
  long totalTime = activeTime + idleTime;
  ans = float(activeTime) / float(totalTime);
  
  // Save the active time and idle time
  this -> prevActiveTime = currActiveTime;
  this -> prevIdleTime = currIdleTime;
  return ans;
}