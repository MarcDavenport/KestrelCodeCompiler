/**
   KString.hpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/14/2018
   Modified : 09/14/2018
   
   KString.hpp contains the interface for working with Kestrel strings
*/



#ifndef KString_HPP
#define KString_HPP

#include <vector>

/// Kestrel strings can contain embedded nulls, hence the need for an alternative to std::string

class KString {
   std::vector<char> str;
public :
   KString();
   KString(const char* cstr);
   
   KString& operator=(const char* cstr);
   
   inline void PushBack(char c) {str.push_back(c);}
   inline void Size() {return str.size();}
   inline bool Empty() {return str.empty();}
   inline void Clear() {str.clear();}
};



#endif // KString_HPP




