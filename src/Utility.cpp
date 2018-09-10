/**
   Utility.cpp by Marc Davenport for Compiler Construction
   Created : 09/07/2018
   Last update : 09/07/2018
   
   The StringPrintF function is borrowed from my GUI library EAGLE.

   It can be found at https://github.com/EdgarReynaldo/EagleGUI under branch master in folder /src/StringWork.cpp
   
   This file contains the implementation of some utilities to make my life easier
*/


#include "Utility.hpp"

#include <cstdarg>
#include <cstdlib>
#include <cstring>





unsigned int STRINGPRINTF_BUFFER_SIZE = 1024;

   
std::string StringPrintF(const char* format_str , ...) {
   char buffer[STRINGPRINTF_BUFFER_SIZE];
   va_list args;
   va_start(args , format_str);
///int vsnprintf (char * s, size_t n, const char * format, va_list arg );
   vsnprintf(buffer , STRINGPRINTF_BUFFER_SIZE , format_str , args);
   va_end(args);
   return std::string(buffer);
}


