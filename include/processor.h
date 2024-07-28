#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();  // (Done)TODO: See src/processor.cpp

  // (Done)TODO: Declare any necessary private members
 private:
  vector<string> cpuTime_;
  long prevActiveTime_{0};
  long prevIdleTime_{0};
};

#endif