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
  char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  std::string outputText {""};
  int inputTextLength = inputText.length();
  outputText.resize(inputTextLength);

  //Encryption option:
  if(encrypt)
    {
    // Loop over the input text
      for (int i = 0;  i <= inputTextLength; i++)
	{
	  // For each character find the corresponding position in the alphabet
	  int j = 0;
	  while(j < 25)
	    {
	      if(inputText[i] == alphabet[j])
		{
		  // Apply the +ve shift to the position, handling correctly potential wrap-around
		  int needWrap = 25-key;
		  if(j< needWrap)
		    {
		      int place = j+key;
		      // Determine the new character and add it to the output string
		      outputText[i] = alphabet[place];
		    }else
		    {
		      int difference = (j+key)-25;
		      // Determine the new character and add it to the output string
		      outputText[i] = alphabet[difference];
		    }
		}
	      j++;
	    }
	}
    }else
    //Decryption option:
    {
     // Loop over the input text
      for (int i = 0; i <= inputTextLength; i++)
	{
	  // For each character find the corresponding position in the alphabet
	  int j = 25;
	  while(j > 0)
	    {
	      if(inputText[i] == alphabet[j])
		{
		  // Apply the -ve shift to the position, handling correctly potential wrap-around
		  int needWrap = 25-key;
		  if(j < needWrap)
		    {
		      int place = j-key;
		      // Determine the new character and add it to the output string
		      outputText[i] = alphabet[place];
		    }else
		    {
		      int difference = 25-(key-j);
		      // Determine the new character and add it to the output string
		      outputText[i] = alphabet[difference];
		    }
		}
	      j--;
	    }
	} 
    }
      // Finally (after the loop), return the output string
      return outputText;
}
