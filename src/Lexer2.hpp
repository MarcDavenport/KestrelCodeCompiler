

#ifndef Lexer2_HPP
#define Lexer2_HPP


#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

#include "KString.hpp"

enum LEX_TYPE {
   LEX_WS      = 0,
   LEX_ID      = 1,
   LEX_STR     = 2,
   LEX_NUM     = 3,
   LEX_BLOCK   = 4,
   LEX_OP      = 5,
   LEX_COMMENT = 6,
   LEX_ERROR   = 7,
   NUM_LEXER_STATES = 8
};

std::string LexerStateTypeString(LEX_TYPE t);


enum LEX_ERROR_TYPE {
   LEX_NOERROR  = 0,
   LEX_NULL     = 1,
   LEX_EXPECT   = 2,
   LEX_UNEXPECT = 3,
   
   
};



class LexToken {
   LEX_TYPE type;
   int line;
   int column;
   KString word;
   
public :
   LexToken(LEX_TYPE t);
   LexToken(LEX_TYPE t , const KString& s);
   
   void SetWord(KString w) {word = w;}
   void SetLine(int l) {line = l;}
   void SetColumn(int c) {column = c;}
   void PushBack(char c) {word.PushBack(c);}
   void Clear();
   
   LEX_TYPE    Type() const {return type;  }
   int         Line() const {return line;  }
   int       Column() const {return column;}
   KString     Word() const {return word;  }
};




typedef LexToken (*LEXFUNC)(std::istream& istrm);

LexToken LexWS   (std::istream& in);
LexToken LexID   (std::istream& in);
LexToken LexSTR  (std::istream& in);
LexToken LexNUM  (std::istream& in);
LexToken LexBLOCK(std::istream& in);
LexToken LexOP   (std::istream& in);
LexToken LexCMT  (std::istream& in);
LexToken LexERR  (std::istream& in);



class Lexer2 {
   
   std::vector<LexToken> tokens;
   


   static const LEXFUNC lexfuncs[NUM_LEXER_STATES];

   
   KString MakeTag(const LexToken& token);
   
public :
   
   Lexer2();
   
   LEX_TYPE LexerState(char ch);

   void Clear();

   void Lexify(std::istream& istrm);

   void WriteTags(std::ostream& os);

   void DumpStateTable(std::ostream& os);
   
   const std::vector<LexToken>& Tokens() {return tokens;}
};



#endif // Lexer2_HPP


