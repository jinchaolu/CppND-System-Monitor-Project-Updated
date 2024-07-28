#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // (Done)TODO: Declare any necessary private members
 private:
  vector<string> cpuTime_;
  long prevActiveTime{0};
  long prevIdleTime{0};
};

#endif