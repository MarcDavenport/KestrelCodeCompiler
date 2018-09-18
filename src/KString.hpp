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
#include <string>
#include <iostream>


/// Kestrel strings can contain embedded nulls, hence the need for an alternative to std::string

/// Some typedefs, so we can change things easier later if needed
typedef char KChar;
typedef std::vector<KChar> KSTR;/// Aka std::string :P

class KString {
   KSTR kstr;
public :
   KString();
   KString(const char* cstr);
   KString(const std::string& str);
   KString(const KSTR& str);
   KString(KSTR::const_iterator first , KSTR::const_iterator last);
   
   KString& operator=(const char* cstr);

   bool operator==(const KString& str) const;

   KSTR::const_iterator Begin() const {return kstr.begin();}
   KSTR::const_iterator End() const {return kstr.end();}

   KSTR::const_iterator Find(const KChar& kc) const;
   
   inline void         PushBack(KChar kc) {kstr.push_back(kc);}

   inline unsigned int Size()  const {return kstr.size();}
   inline bool         Empty() const {return kstr.empty();}
   inline void         Clear() {kstr.clear();}

   inline const        KChar& operator[](unsigned int index) const {return kstr[index];}
   
   inline const KSTR& KStr() const {return kstr;}
   
   friend std::ostream& operator<<(std::ostream& os , const KString& kstr);
};



/// Borrowed from stack overflow here : 
/// https://stackoverflow.com/questions/8157937/how-to-specialize-stdhashkeyoperator-for-user-defined-type-in-unordered
/// Specializing std::hash<KString>


extern size_t HASH_MULTIPLIER;
extern size_t HASH_DIFFERENCE;
extern size_t HASH_TABLESIZE;


namespace std {
   template <> struct hash<KString> {
      size_t operator()(const KString& kst) const;
   };
};


inline std::ostream& operator<<(std::ostream& os , const KString& kstr) {
   for (unsigned int i = 0 ; i < kstr.Size() ; ++i) {
      os << kstr[i];
   }
   return os;
}



#endif // KString_HPP




