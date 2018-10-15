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
#include <unordered_map>
#include <map>



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

enum OPNUM {
   OP_ADDRESS = 0,
   OP_FIELD   = 1,
   OP_DEFINE  = 2,
   OP_COMMA   = 3,
   OP_RANGE   = 4,
   OP_MULT    = 5,
   OP_DIV     = 6,
   OP_MOD     = 7,
   OP_PLUS    = 8,
   OP_MINUS   = 9,
   OP_NOT     = 10,
   OP_AND     = 11,
   OP_OR      = 12,
   OP_GTHAN   = 13,
   OP_LTHAN   = 14,
   OP_NEQUAL  = 15,
   OP_GEQUAL  = 16,
   OP_LEQUAL  = 17,
   OP_ASSIGN  = 18,
   OP_STOP    = 19,
   NUM_OPS    = 20
};

extern const std::vector<std::string> opstrs;

std::string OpStr(OPNUM op);

extern const std::unordered_map<KString , OPNUM> operator_set;/// All operator strings

OPNUM GetOp(const KString& kstr);

enum KEYWORD_TYPE {
   /// KWG_MODIFIER
   KW_MOD_CONST        = 0,
   KW_MOD_FINAL        = 1,
   /// KWG_DECLARATION
   KW_DEC_VAR          = 2,
   KW_DEC_PROC         = 3,
   KW_DEC_FUNC         = 4,
   /// KWG_ACCESS
   KW_ACC_PRIV         = 5,
   KW_ACC_RESTRICT     = 6,
   KW_MOD_EXTERNAL     = 7,
   /// KWG_TYPE
   KW_TYPE_TYPE        = 8,
   KW_TYPE_ENUM        = 9,
   KW_TYPE_ARRAY       = 10,
   KW_TYPE_SET         = 11,
   KW_TYPE_RECORD      = 12,
   KW_TYPE_OF          = 13,
   /// KWG_RANGE
   KW_RANGE_IN         = 14,
   /// KWG_CONTROL
   KW_CONTROL_IF       = 15,
   KW_CONTROL_THEN     = 16,
   KW_CONTROL_ELSE     = 17,
   KW_CONTROL_END      = 18,
   KW_CONTROL_SELECT   = 19,
   KW_CONTROL_CASE     = 20,
   /// KWG_LOOP
   KW_LOOP_WHILE       = 21,
   KW_LOOP_DO          = 22,
   KW_LOOP_UNTIL       = 23,
   KW_LOOP_FOR         = 24,
   /// KWG_EXCEPTION
   KW_EXCEPT_EXCEPTION = 25,
   KW_EXCEPT_RAISE     = 26,
   KW_EXCEPT_CATCH     = 27,
   KW_EXCEPT_RETURN    = 28,
   /// KWG_NULLPTR
   KW_NULL_NULL        = 29,
   NUM_KEYWORDS        = 30
};

enum KEYWORD_GROUP {
   KWG_MODIFIER = 0,
   KWG_DECLARATION = 1,
   KWG_ACCESS = 2,
   KWG_TYPE = 3,
   KWG_RANGE = 4,/// ??? in?, of? what are these
   KWG_CONTROL = 5,
   KWG_LOOP = 6,
   KWG_EXCEPTION = 7,
   KWG_NULLPTR = 8,
   NUM_KEYWORD_GROUPS = 9
};

std::string KWStr(KEYWORD_TYPE k);




#endif // Data_HPP





