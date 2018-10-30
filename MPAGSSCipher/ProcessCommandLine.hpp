#ifndef MPAGSSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSSCIPHER_PROCESSCOMMANDLINE_HPP

#include <string>

//Process command line arguments
bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
			bool& helpRequested,
			bool& versionRequested,
			bool& iFile,
			bool& oFile,
			std::string& inputFileName,
			std::string& outputFileName);

#endif  //MPAGSSCIPHER_PROCESSCOMMANDLINE_HPP
