#ifndef MPAGSSCIPHER_CAESARCIPHER_HPP
#define MPAGSSCIPHER_CAESARCIPHER_HPP

#include <string>

//Transliterate char to string
std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt);

#endif  //MPAGSSCIPHER_CAESARCIPHER_HPP
