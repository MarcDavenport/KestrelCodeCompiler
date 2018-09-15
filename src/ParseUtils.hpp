/**
   ParseUtils.hpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/14/2018
   Modified : 09/14/2018
   
   ParseUtils.hpp contains the interface for some parsing utility functions like base conversion
*/

#ifndef ParseUtils_HPP
#define ParseUtils_HPP



class KString;

char CrockfordToDigit(char c32);/// returns a char in the range [0,32)

int CrockfordToDecimal(unsigned short base , const KString& c32str);

KString DecimalToCrockford(int decimal , short newbase) {



#endif // ParseUtils_HPP




