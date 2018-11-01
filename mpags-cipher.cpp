// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Our project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "CaesarCipher.hpp"

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
  bool encrypt {false};
  bool decrypt {false};
  std::string inputFile {""};
  std::string outputFile {""};
  std::string key {""};
 
  // Call processCommandLine function to handle command-line arguments
  bool process { processCommandLine(cmdLineArgs, helpRequested, versionRequested, encrypt, decrypt, key, inputFile, outputFile) };
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
      << "                   Stdout will be used if not supplied\n\n"
      << "  -e               Encrypt text, provide encription key after this argument\n"
      << "  -d               Decrypt text, provide encription key after this argument\n"; 
    // Help requires no further action, so return from function
    // with true used to indicate success
    return 0;
  }

// Handle version, if requested
  // Like help, requires no further action,
  // so return from function with true to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input and output text
  char inputChar {'x'};
  std::string inputText {""};
  std::string outputText {""};

  // Read in user input from stdin/file
  // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)
  if (!inputFile.empty())
    {
      std::ifstream in_file {inputFile};
      bool ok_to_read = in_file.good();
      if(ok_to_read == true)
	{
	  while (in_file >> inputChar)
	    {
	      inputText += transformChar(inputChar);
	    }
	}else
	{
	  std::cerr << "[error] Cannot open input file \n";
	  return 1;
	}
    }
  else
    {
      while(std::cin >> inputChar)
        {
	  inputText += transformChar(inputChar);
        }
    }


    // Encription or decryption

    if (encrypt || decrypt)
      {
	if ( key.front() == '-' ) {
	  std::cerr << "[error] key must be positive integer" << std::endl;
	  return 1;
	}
	unsigned long int caesar_key { std::stoul(key) };
	outputText = runCaesarCipher(inputText, caesar_key, encrypt);
      }
    else
      {
	outputText = inputText;
      }
    
    // Output the transliterated text
    if (!outputFile.empty())
      {
	std::ofstream out_file {outputFile};
	bool ok_to_write = out_file.good();
	if(ok_to_write == true)
	  {
	    out_file << outputText << "\n";
	  }
	else
	  {
	    std::cerr << "[error] Cannot open output file \n";
	    return 1;
	  }
      }
    else
      {
	std::cout << outputText << std::endl;
      }

      // No requirement to return from main, but we do so for clarity
      // and for consistency with other functions
      return 0;
}




