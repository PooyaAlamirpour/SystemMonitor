#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream> // debugging

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
  string os, kernel;
  string line, hlp;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >>hlp>> kernel;
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

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {

  string line;
  string key ="";
  string value="";
  string value_tmem ="";
  string value_fmem ="";
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:")
          value_tmem =value;
        if (key == "MemFree:")
          value_fmem =value;
      }
      if ((value_fmem !="") &&(value_tmem!=""))
        break;
    }
    filestream.close();
  }
  return ( (std::stof(value_tmem) - std::stof(value_fmem)) /
          std::stof(value_tmem));

 }

// Done: Read and return the system uptime
long LinuxParser::UpTime() {

  string line;
  string value="";
  std::ifstream filestream(kProcDirectory+kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return (std::stol(value));
 }

// Done: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {

  string line ="";
  string cpu="";
  string sUser="", sNice ="",sSystem="",sIdle="", sIOwait="",
         sIRQ="", sSoftIRQ="",sSteal="",sGuest="", sGuestNice="";
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> sUser>> sNice >>sSystem>>sIdle>>sIOwait>>
               sIRQ>> sSoftIRQ>>sSteal>>sGuest>>sGuestNice;
  }
  return (std::stol(sUser)+std::stol(sNice)+std::stol(sSystem)+std::stol(sIRQ)+
          std::stol(sSoftIRQ)+std::stol(sSteal)+std::stol(sGuest)+ std::stol(sGuestNice)+
          std::stol(sIdle)+std::stol(sIOwait));
}

// Done: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {

  string line ="",shlp="";
  string sUtime="", sStime ="",sCUtime="",sCStime="";
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i=1; i<14; i++)
      linestream >> shlp;
    linestream >> sUtime >> sStime>> sCUtime >>sCStime;
  }
  return (std::stol(sUtime)+std::stol(sStime)+
          std::stol(sCUtime)+std::stol(sCStime));
}

// Done: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {

  string line ="";
  string cpu="";
  string sUser="", sNice ="",sSystem="",sIdle="", sIOwait="",
         sIRQ="", sSoftIRQ="",sSteal="",sGuest="", sGuestNice="";
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> sUser>> sNice >>sSystem>>sIdle>>sIOwait>>
               sIRQ>> sSoftIRQ>>sSteal>>sGuest>>sGuestNice;
  }
  return (std::stol(sUser)+std::stol(sNice)+std::stol(sSystem)+std::stol(sIRQ)+
          std::stol(sSoftIRQ)+std::stol(sSteal)+std::stol(sGuest)+ std::stol(sGuestNice));
}

// Done: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {

  string line ="";
  string cpu="";
  string sUser="", sNice ="",sSystem="",sIdle="", sIOwait="",
         sIRQ="", sSoftIRQ="",sSteal="",sGuest="", sGuestNice="";
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> sUser>> sNice >>sSystem>>sIdle>>sIOwait>>
               sIRQ>> sSoftIRQ>>sSteal>>sGuest>>sGuestNice;
  }
  return (std::stol(sIdle)+std::stol(sIOwait));
}

// Done: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  long lOldActiveJiffies =ActiveJiffies();
  long lOldIdleJiffies = IdleJiffies();
  sleep (10);
  long lActiveJiffies =ActiveJiffies();
  long lIdleJiffies =IdleJiffies();

  string shlp=Format::ElapsedTime(
    ((lActiveJiffies-lOldActiveJiffies)- (lIdleJiffies-lOldIdleJiffies))/
     (lActiveJiffies-lOldActiveJiffies));
  vector<string> vResult;
  vResult.push_back (shlp);
  return vResult;
}

// Done: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key ="";
  string value="";
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes")
          return std::stoi(value);
    }
  }
  return 0; // should never happen
}

// Done: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key ="";
  string value="";
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running")
          return std::stoi(value);
    }
  }
  return 0; // should never happen
}

// Done: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    return line;
  }
  return ""; // should never happen
}


// Done: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  string key ="";
  string value="";
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmData:"){
          int tmp= (100 * std::stof(value)/1024+0.5);
          return to_string(tmp/100)+"."+((tmp%100 <10) ? "0"+to_string(tmp%100):to_string(tmp%100));
      }

    }
  }
  return ""; // should never happen
}

// Done: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
    string line;
  string key ="";
  string value="";
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:")
          return value;
    }
  }
  return ""; // should never happen
}


// Done: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line;
  string search_token ="x:"+to_string(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      auto pos =line.find(search_token);
      if (pos != string::npos)
          return line.substr(0,pos-1);
    }
  }
  return "root"; // default value
}


// Done: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line,hlp;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i=0; i < 20; i++)
      linestream >> hlp;
    return stol(hlp);

  }
  return 0; // should never happen
}
