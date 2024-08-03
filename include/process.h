#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

using std::string;
using std::vector;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               // (Done)TODO: See src/process.cpp
  std::string User();                      // (Done)TODO: See src/process.cpp
  std::string Command();                   // (Done)TODO: See src/process.cpp
  float CpuUtilization();                  // (Done)TODO: See src/process.cpp
  std::string Ram();                       // (Done)TODO: See src/process.cpp
  long int UpTime();                       // (Done)TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // (Done)TODO: See src/process.cpp
  bool operator>(Process const& a) const;  // (Done)TODO: See src/process.cpp

  // (Done)TODO: Declare any necessary private members
 private:
  int pid_;
  float cpuUtilization_{0.0};
  vector<string> cpuTime_;
  long prevActiveTime_{0};
  long prevIdleTime_{0};
};

#endif