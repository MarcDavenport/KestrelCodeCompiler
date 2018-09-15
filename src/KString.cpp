/**
   KString.cpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/14/2018
   Modified : 09/14/2018
   
   KString.cpp contains the implementation for working with Kestrel strings
*/



#include "KString.hpp"



KString::KString() :
      str()
{}



KString::KString(const char* cstr) :
      str()
{
   *this = cstr;
}



KString& operator=(const char* cstr) {
   int sz = strlen(cstr) + 1;/// cstrings have a null character at the end
   str.resize(sz);
   strncpy(&str[0] , cstr , sz);
   str.pop_back();/// Remove the '\0'
   return *this;
}
