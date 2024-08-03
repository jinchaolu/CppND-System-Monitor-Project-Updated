#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
long Jiffies(vector<string> cpuTime);
long ActiveJiffies(vector<string> cpuTime);
long ActiveJiffies(int pid);
long IdleJiffies(vector<string> cpuTime);

// Processes
enum ProcessStates {
  kUtime_ = 13, // CPU time spent in user code, measured in clock ticks
  kStime_, // CPU time spent in kernel code, measured in clock ticks
  kCutime_, // Waited-for children's CPU time spent in user code (in clock ticks)
  kCstime_, // Waited-for children's CPU time spent in kernel code (in clock ticks)
  kStarttime_ = 21, // Time when the process started, measured in clock ticks
};
std::vector<std::string> CpuUtilization(int pid);
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif