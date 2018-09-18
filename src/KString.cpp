/**
   KString.cpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/14/2018
   Modified : 09/14/2018
   
   KString.cpp contains the implementation for working with Kestrel strings
*/



#include "KString.hpp"


#include <cstring>


size_t HASH_MULTIPLIER = 261127;/// PRIME
size_t HASH_DIFFERENCE = 0;
size_t HASH_TABLESIZE = 521;/// PRIME



namespace std {
   size_t hash<KString>::operator()(const KString& kst) const
   {
      const size_t M = HASH_MULTIPLIER;
      const size_t D = HASH_DIFFERENCE;
      const size_t K = HASH_TABLESIZE;

      const size_t seed = kst.Size();

      size_t khash = std::hash<size_t>()(seed);

      for (unsigned int i = 0 ; i < kst.Size() ; ++i) {
         khash = ((std::hash<size_t>()(khash*(size_t)kst[i]) * M) + D) % K;
      }
      /* your code here, e.g. "return hash<int>()(x.value);" */
      /// return std::hash<std::vector<KChar> >(kst.Word());/// only hash<vector<bool> > is implemented for vectors
      return khash;
   }
};



KString::KString() :
      kstr()
{}



KString::KString(const char* cstr) :
      kstr()
{
   *this = cstr;
}



KString::KString(const std::string& str) :
      kstr()
{
   *this = str.c_str();
}



KString::KString(const KSTR& str) :
      kstr(str)
{}



KString::KString(KSTR::const_iterator first , KSTR::const_iterator last) :
      kstr(first , last)
{}



KString& KString::operator=(const char* cstr) {
   int sz = strlen(cstr) + 1;/// cstrings have a null character at the end
   kstr.resize(sz);
   strncpy(&kstr[0] , cstr , sz);/// TODO : This uses a pointer to kstr which is a vector of KChar (currently typedef'ed to char)
   kstr.pop_back();/// Remove the '\0'
   return *this;
}



bool KString::operator==(const KString& str) const {
   return kstr == str.kstr;
}



KSTR::const_iterator KString::Find(const KChar& kc) const {
   /// return kstr.find(kc);/// If only vector had find...
   KSTR::const_iterator it = kstr.begin();
   while (it != kstr.end()) {
      if (*it == kc) {
         break;
      }
      ++it;
   }
   return it;
}







