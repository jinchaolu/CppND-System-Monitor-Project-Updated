#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// (Done)TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  string sMemTotal;
  string sMemFree;
  string sMemAvailable;
  string sBuffers;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          sMemTotal = value;
        }
        if (key == "MemFree:") {
          sMemFree = value;
        }
        if (key == "MemAvailable:") {
          sMemAvailable = value;
        }
        if (key == "Buffers:") {
          sBuffers = value;
        }
      }
    }
  }
  float totalMem = std::stof(sMemTotal);
  float freeMem = std::stof(sMemFree);
  return ((totalMem - freeMem) / totalMem);
}

// (Done)TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  float fUpTime;
  float fIdleTime;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> fUpTime >> fIdleTime;
    // std::cout << fUpTime << " " << fIdleTime << std::endl;
  }
  return long(fUpTime);
}

// (Done)TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies(vector<string> cpuTime) {
  return (LinuxParser::ActiveJiffies(cpuTime) + LinuxParser::IdleJiffies(cpuTime));
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// (Done)TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies(vector<string> cpuTime) {
  return (
    std::stol(cpuTime[CPUStates::kUser_]) + std::stol(cpuTime[CPUStates::kNice_])
    + std::stol(cpuTime[CPUStates::kSystem_]) + std::stol(cpuTime[CPUStates::kIRQ_])
    + std::stol(cpuTime[CPUStates::kSoftIRQ_]) + std::stol(cpuTime[CPUStates::kSteal_])
    + std::stol(cpuTime[CPUStates::kGuest_]) + std::stol(cpuTime[CPUStates::kGuestNice_])
         );
}

// (Done)TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies(vector<string> cpuTime) {
  return (std::stol(cpuTime[CPUStates::kIdle_]) + std::stol(cpuTime[CPUStates::kIOwait_]));
}

// (Done)TODO: Read and return CPU utilization
// Even once you know what each of these numbers represents, it's
// still a challenge to determine exactly how to use these figures
// to calculate processor utilization. This guide(https://github.com/Leo-G/Data-Science-Wiki)
// and this StackOverflow post(https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux) are helpful.
// Example:
//   cpu  802329 6142 358209 30954390 309714 0 30751 0 0 0
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string key;
  string value;
  vector<string> ans;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
//         std::cout << key << std::endl;
        while (linestream >> value) {
//           std::cout << value << std::endl;
          ans.push_back(value);
        }
      }
    }
  }
  return ans;
}

// (Done)TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  string sTotalProcesses;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          sTotalProcesses = value;
        }
      }
    }
  }
  return (std::stoi(sTotalProcesses));
}

// (Done)TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  string sRunningProcesses;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          sRunningProcesses = value;
        }
      }
    }
  }
  return (std::stoi(sRunningProcesses));
}

vector<string> LinuxParser::CpuUtilization(int pid) {
  string line;
  string key;
  string value;
  vector<string> ans;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
//         std::cout << key << std::endl;
        while (linestream >> value) {
//           std::cout << value << std::endl;
          ans.push_back(value);
        }
      }
    }
  }
  return ans;
}

// (Done)TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line{""};
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
//   std::cout << kProcDirectory + std::to_string(pid) + kCmdlineFilename << std::endl;
  if (stream.is_open()) {
    std::getline(stream, line);
//     std::cout << line << std::endl;
  }
  return line;
}

// (Done) TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
//   std::cout << kProcDirectory + std::to_string(pid) + kStatusFilename << std::endl;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "VmSize:") {
//         std::cout << key << std::endl;
        linestream >> value;
//         std::cout << value << std::endl;
      }
    }
  }
  // Convert from kb to mb
  // 1 kb == 0.001 mb
  string temp = std::to_string(std::stof(value) * 0.001);
//   std::cout << temp.substr(0, temp.size() - 4) << std::endl;
  return temp.substr(0, temp.size() - 4);
}

// (Done)TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string value;
  
  // Get the UID associated with the process
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "Uid:") {
//         std::cout << key << std::endl;
        linestream >> value;
//         std::cout << value << std::endl;
      }
    }
  }
  return value;
}

// (Done)TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  // Get the user corresponding to that UID
  string uid = LinuxParser::Uid(pid);
  string line;
  string name;
  string value;
  int index = 1;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      // Name is the first word
      linestream >> name;
      // UID is the third word
      int i = 0;
      while (i <= index && linestream >> value) {
        i++;
      }
      // If value matches UID, return
      if (value == uid) {
        return name;
      }
    }
  }

  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
