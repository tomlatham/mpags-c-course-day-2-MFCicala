// Standard Library includes
#include <iostream>
#include <string>
#include <vector>

// Our project headers
#include "CaesarCipher.hpp"

//caesarCipher function:

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt)
{
  // Create the alphabet container and output string
  const std::vector<char> alphabet = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  const size_t alphabetSize {alphabet.size()};

  std::string outputText {""};
  outputText.reserve(inputText.length());

  // Make sure that the key is in the range 0 - 25
  const size_t truncatedKey { key % alphabetSize };

  // Loop over the input text
  for ( const char& inputChar : inputText )
    {
      // For each character find the corresponding position in the alphabet
      for ( size_t j {0}; j < alphabetSize; ++j )
        {
	  if(inputChar == alphabet[j])
	    {
	      // Apply the shift to the position, handling correctly potential wrap-around
	      if( encrypt )
	        {
		  const size_t place = (j + truncatedKey) % alphabetSize;
		  // Determine the new character and add it to the output string
		  outputText += alphabet[place];
		}
	      else
	        {
		  const size_t place = (j + alphabetSize - truncatedKey) % alphabetSize;
		  // Determine the new character and add it to the output string
		  outputText += alphabet[place];
		}

	      break;
	    }
	}
    }

  // Finally (after the loop), return the output string
  return outputText;
}
