#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <sstream>
#include <iomanip> // used format command setw

namespace Format {
std::string ElapsedTime(long times);  // TODO: See src/format.cpp
};                                    // namespace Format

#endif