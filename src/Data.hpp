/**
   Data.hpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/18/2018
   Modified : 09/18/2018
   
   Data.hpp contains the interface to common data used by the kestrel compiler
*/

#ifndef Data_HPP
#define Data_HPP

#include <unordered_set>

#include "KString.hpp"


/// For the lexer

extern const std::unordered_set<KChar> quotechars;/// Contains quote chararcters
extern const std::unordered_set<KChar> blockchars;/// For code blocks - contains parentheses, brackets, and braces

extern const std::unordered_set<KChar> opchars;

/// For the parser

extern const std::unordered_set<KChar> block_openset;
extern const std::unordered_set<KChar> block_closeset;

extern const std::unordered_set<KString> reserved_words;
extern const std::vector< std::unordered_set<KString> > reserved_word_sets;

extern const std::unordered_set<KString> operator_set2;/// All operators of length 2
extern const std::unordered_set<KString> operator_set1;/// All operators of length 1
extern const std::unordered_set<KString> operator_set_math;
extern const std::unordered_set<KString> operator_set_logic;




#endif // Data_HPP





