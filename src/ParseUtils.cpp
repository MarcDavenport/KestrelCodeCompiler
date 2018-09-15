/**
   ParseUtils.cpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/14/2018
   Modified : 09/14/2018
   
   ParseUtils.cpp contains the implementation for utilities like base conversion using Crockford's scheme
*/



#include "ParseUtils.hpp"


#include "KString.hpp"
#include "Exception.hpp"
#include "Utility.hpp"

#include <cstring>



/** Crockford lookup table
   digit	0 	1  2 	3  4 	5  6 	7 
   value	0 	1 	3 	3 	4 	5 	6 	7
   digit	8	9	Aa	Bb Cc	Dd	Ee	Ff
   value	8 	9 	10 11 12 13 14 15
   digit	Gg	Hh	Ii	Jj Kk	Ll	Mm	Nn
   value	16 17 1 	18 19 1 	20 21
   digit	Oo	Pp	Qq	Rr Ss	Tt	Uu	Vv
   value	0 	22 23 24 25 26 32 27
   digit	Ww	Xx	Yy	Zz
   value	28 29 30 31    
*/



char CrockfordToDigit(char c32) {
   /// CrockfordToDecimal maps a Crockford letter to a decimal digit returned as a char type.

   /// Sanity check
   if ((!isdigit(c32) && !isalpha(c32)) || (c == 'u' || c == 'U') {/// U and u are invalid in base 32, they map to 32
      throw Exception(StringPrintF(
         "CrockfordToDecimal(char c32) : c32 (%c) is an invalid character! c32 must be a letter or digit excluding U." , c32
      ));
   }

   /// static lookup table
   static char valtable[128] = {-1};/// Initialize to an invalid value, this will be used for error checking
   static bool table_ready = false;
   if (!table_ready) {/// First run, we need to build the lookup table
      /// digits
      for (char c = '0' ; c <= '9' ; ++c) {
         valtable[(int)c] = (int)(c - '0');/// 0 thru 9
      }
      /// lowercase
      for (char c = 'a' ; c <= 'z' ; ++c) {
         if (c == 'l' || c == 'i') {
            valtable[(int)c] = (char)1;/// l and i map to one
         }
         else if (c == 'o') {
            valtable[(int)c] = (char)0;/// o maps to zero
         }
         else {
            valtable[(int)c] = (int)(c - 'a') + 10;/// 10 thru 31
         }
      }
      /// uppercase
      for (char c = 'A' ; c <= 'Z' ; ++c) {
         if (c == 'L' || c == 'I') {
            valtable[(int)c] = (char)1;/// L and I map to one
         }
         else if (c == 'O') {
            valtable[(int)c] = (char)0;/// O maps to zero
         }
         else {
            valtable[(int)c] = (int)(c - 'A') + 10;/// 10 thru 31
         }
      }
      table_ready = true;
   }
   
   /// Lookup
   char d = valtable[(int)c32];
   /// Sanity check
   EAGLE_ASSERT((int)d >= 0 && (int)d < 32);

   return d;
}



int CrockfordToDecimal(unsigned short base , std::string c32) {
   if (c32.empty()) {return 0;}
   
   const int BASE = 10;

   bool neg = c32[0] == '-';
   int start = 0;
   if (neg) {start = 1;}

   int value = 0;
   
   for (unsigned int i = start ; i < c32.size() ; ++i) {
      value *= base;/// Okay for the first digit, 0 * base is still zero
      int val = (int)CrockfordToDecimal(c32[i]);/// Crockford letter i's decimal value
      value += val;
   }
   return value;
}



KString DecimalToCrockford(int decimal , short newbase) {
   static const char* alphabet = "0123456789abcdefghjkmnpqrstvwxyz";/// Crockford's base 32 alphabet

   if (newbase < 0 || newbase >= 32) {
      throw RuntimeError(StringPrintF("DecimalToCrockford : base %d is invalid or unsupported!\n" , (int)base));
   }
   bool neg = decimal < 0;
   decimal = abs(decimal);
   
   std::stack<char> digitstack;
   do {
      digitstack.push_back(alphabet[decimal%newbase]);
      decimal /= newbase;
   } while (decimal > 0);
   
   KString digitstr;
   if (neg) {
      digitstr += '-';
   }
   while (!digitstack.empty()) {
      digitstr += digitstack.back();
      digitstack.pop_back();
   }
   return digitstr;
}


