#include <string>
#include <iostream>
#include "format.h"

using std::string;

// (Done)TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
//   std::cout << "seconds" << seconds << std::endl;
  int ss = seconds % 60;
  string sSecond = ((ss < 10) ? ("0" + std::to_string(ss)) : (std::to_string(ss)));
//   std::cout << "ss: " << sSecond << std::endl;
  seconds /= 60;
  int mm = seconds % 60;
  string sMinute = ((mm < 10) ? ("0" + std::to_string(mm)) : (std::to_string(mm)));
//   std::cout << "mm: " << sMinute << std::endl;
  seconds /= 60;
  int hh = seconds;
  string sHour = ((hh < 10) ? ("0" + std::to_string(hh)) : (std::to_string(hh)));
//   std::cout << "hh: " << sHour << std::endl;
  return (sHour + ":" + sMinute + ":" + sSecond);
}