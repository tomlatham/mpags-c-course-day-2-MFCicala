// Standard Library includes
#include <iostream>
#include <string>
#include <vector>

// For std::isalpha and std::isupper
#include <cctype>

//Functions
std::string transformChar(const char in_char)
{
  /* transliterate digts to English words and lowercase to uppercase characters

     const char in_char: character to transliterate

     return: the string of transliterated characters
  */

  char inputChar {in_char};
  std::string inputText;

  // Uppercase alphabetic characters
  if (std::isalpha(inputChar)) {
    inputText += std::toupper(inputChar);
  }
  
  // Transliterate digits to English words
  switch (inputChar) {
  case '0':
    inputText += "ZERO";
    break;
  case '1':
    inputText += "ONE";
    break;
  case '2':
    inputText += "TWO";
    break;
  case '3':
    inputText += "THREE";
    break;
  case '4':
    inputText += "FOUR";
    break;
  case '5':
    inputText += "FIVE";
    break;
  case '6':
    inputText += "SIX";
    break;
  case '7':
    inputText += "SEVEN";
    break;
  case '8':
    inputText += "EIGHT";
    break;
  case '9':
    inputText += "NINE";
    break;
  }
  
  // If the character isn't alphabetic or numeric, DONT add it.
  // Our ciphers can only operate on alphabetic characters.

  return inputText;
}

bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
			bool& helpRequested,
			bool& versionRequested,
			std::string& inputFileName,
			std::string& outputFileName)
{
  /* Handle command-line arguments

     std::vector<std::string>& args:   reference to vector of command-line arguments
     
     bool& helpRequested:              reference to helpRequested flag

     bool& versionRequested:           reference to versionRequested flag

     std::string& inputFileName:       reference to inputFileName string 

     std::string& outputFileName:      reference to outputFileName string

     return: no problems true, problems false
  */


  std::cout<<"In function now \n!";

 // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {cmdLineArgs.size()};

 // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
  for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
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



// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
 
  // Call processCommandLine function to handle command-line arguments
  bool process = processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile);
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
  while(std::cin >> inputChar)
    {
      inputText = transformChar(inputChar);
      
      // Output the transliterated text
      // Warn that output file option not yet implemented
      if (!outputFile.empty()) {
	std::cout << "[warning] output to file ('"
		  << outputFile
		  << "') not implemented yet, using stdout\n";
      }
      
      std::cout << inputText << std::endl;
      
      // No requirement to return from main, but we do so for clarity
      // and for consistency with other functions
      return 0;
    }
}
