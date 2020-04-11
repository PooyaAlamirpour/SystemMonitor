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

Process::Process(int pid) {
    pid_ = pid;
}

bool Process::operator>(const Process& a) const {
    return CpuUtilization() > a.CpuUtilization();
}

bool Process::operator<(const Process& a) const {
    return CpuUtilization() < a.CpuUtilization();
}

// Done: Return this process's ID
int Process::Pid() { return pid_; }

// Done: Return this process's CPU utilization
float Process::CpuUtilization() const{
    return cpu_;
}

// Done: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// Done: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// Done: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// Done: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_);}

// Done: Overload the "less than" comparison operator for Process objects
void Process::CpuUtilization(long process_ticks, long system_ticks) {

  long duration_process=process_ticks - cached_process_ticks_;
  long duration = system_ticks - cached_system_ticks_;

  cpu_ = static_cast<float>(duration_process) / duration;

  cached_process_ticks_ = process_ticks;
  cached_system_ticks_ = system_ticks;
}
