// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Our project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"

// For std::isalpha and std::isupper
#include <cctype>


// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  bool iFile {false};
  bool oFile {false};
  std::string inputFile {""};
  std::string outputFile {""};
 
  // Call processCommandLine function to handle command-line arguments
  bool process = processCommandLine(cmdLineArgs, helpRequested, versionRequested, iFile, oFile, inputFile, outputFile);
  if (process == false) 
    {
      return 1;
    }

 // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
    // Help requires no further action, so return from function
    // with true used to indicate success
    return true;
  }

// Handle version, if requested
  // Like help, requires no further action,
  // so return from function with true to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return true;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  // Read in user input from stdin/file
  // Warn that input file option not yet implemented
  if (!inputFile.empty()) {
    std::cout << "[warning] input from file ('"
              << inputFile
              << "') not implemented yet, using stdin\n";
  }


 // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)
  if (iFile == true)
    {
      std::ifstream in_file {inputFile};
      bool ok_to_read = in_file.good();
      if(ok_to_read == true)
	{
	  while (in_file >> inputChar)
	    {
	      inputText = transformChar(inputChar);
	    }
	}else
	{
	  std::cout << "Cannot open input file \n";
	}
    }
  {
    while(std::cin >> inputChar)
      {
	inputText = transformChar(inputChar);
      }
    
    // Output the transliterated text
    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
      std::cout << "[warning] output to file ('"
		<< outputFile
		<< "') not implemented yet, using stdout\n";
    }
    
      if (oFile == true)
	{
	  std::ofstream out_file {outputFile, std::ios::app};
	  bool ok_to_write = out_file.good();
	  if(ok_to_write == true)
	    {
	      out_file << inputText << "\n";
	    }else
	    {
	      std::cout << "Cannot open output file \n";
	    }
	}else
	{
	  std::cout << inputText << std::endl;
	}
      // No requirement to return from main, but we do so for clarity
      // and for consistency with other functions
      return 0;
    }
}




