#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  Processor(); 
  float Utilization();  // TODO: See src/processor.cpp
   
  // TODO: Declare any necessary private members
 private:
   int tAll_  =0;
   int tIdle_ =0;
};

#endif