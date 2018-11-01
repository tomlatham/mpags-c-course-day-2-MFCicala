// Standard Library includes
#include <iostream>
#include <string>
#include <vector>

// Our project headers
#include "ProcessCommandLine.hpp"

//Process command line arguments
bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
			bool& helpRequested,
			bool& versionRequested,
			bool& iFile,
			bool& oFile,
			bool& encrypt,
			bool& decrypt,
			std::string& k,
			std::string& inputFileName,
			std::string& outputFileName)
{
  /* Handle command-line arguments

     std::vector<std::string>& args:   reference to vector of command-line arguments
     
     bool& helpRequested:              reference to helpRequested flag

     bool& versionRequested:           reference to versionRequested flag

     bool& iFile                       reference to inputFile flag
     
     bool& oFile                       reference to outputFile flag
     
     bool& encrypt                     reference to encryption flag

     bool& decrypt                     reference to decryption flag

     std::string& k:                   reference to k string

     std::string& inputFileName:       reference to inputFileName string 

     std::string& outputFileName:      reference to outputFileName string

     return: no problems true, problems false
  */


  //std::cout<<"In function now \n!";

 // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {cmdLineArgs.size()};

 // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
  for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (cmdLineArgs[i] == "-e")
      {
	// Handle encrypt option
	// Next element is key unless -i is the last argument
	if (i == nCmdLineArgs-1) {
	  std::cerr << "[error] -e requires a key argument" << std::endl;
	  // exit main with false return to indicate failure
	  return false;
	}
	else {
	  // Got key so assign it and advance past it
	  encrypt = true;
	  k = cmdLineArgs[i+1];
	}
      }else if (cmdLineArgs[i] == "-d")
      {
	// Handle decrypt option
	// Next element is key unless -i is the last argument
	if (i == nCmdLineArgs-1) {
	  std::cerr << "[error] -d requires a key argument" << std::endl;
	  // exit main with false return to indicate failure
	  return false;
	}
	else {
	  // Got key so assign it and advance past it
	  decrypt = true;
	  k = cmdLineArgs[i+1];
	}
      }else if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
      helpRequested = true;
    }
    else if (cmdLineArgs[i] == "--version") {
      versionRequested = true;
    }
    else if (cmdLineArgs[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	// exit main with false return to indicate failure
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	inputFileName = cmdLineArgs[i+1];
	iFile = true;
	++i;
      }
    }
    else if (cmdLineArgs[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	// exit main with false return to indicate failure
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	outputFileName = cmdLineArgs[i+1];
	oFile = true;
	++i;
      }
    }
    else {
      // Have an unknown flag to output error message and return false
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << cmdLineArgs[i] << "'\n";
      return false;
    }
  }
  return true;
}
