



#ifndef Parser2_HPP
#define Parser2_HPP


#include "Lexer2.hpp"


enum PARSE_TYPE {
   PARSE_WS = 0,
   PARSE_KEYWORD = 1,
   PARSE_IDENTIFIER = 2,
   PARSE_NUMBER = 3,
   PARSE_BLOCK = 4,
   PARSE_OPERATOR = 5,
   PARSE_ERROR = 6,
   NUM_PARSE_TYPES = 7
};

/// ParseTokenBase is a base class, extended to store specific information on Lexical words, rather than trying to
/// mash all the data into a single union or class

class ParseTokenBase {
protected :
   LexToken lextoken;
public :
   ParseToken(const LexToken& token) : lextoken(token) {}
   
   LexToken LexerToken() {return lextoken;}
   
   virtual PARSE_TYPE ParserType()=0;
};



/** Classes derived from ParseTokenBase */



class ParseTokenWS : public ParseTokenBase {
public :
   ParseTokenWS(const LexToken& token);
   
   inline override ParserType() {return PARSE_WS;}
};



class ParseTokenNUM : public  ParseTokenBase {
protected :
   unsigned short base;
   KString val;
   int dval;
public :
   ParseTokenNUM(const LexToken& ltoken , unsigned short numbase , KString numval) :
      
   inline unsigned short Base() const {return base;}
   inline KString KStrValue()   const {return val;}
   inline int DecimalValue()    const {return dval;}
   
   inline override PARSE_TYPE ParserType() {return PARSE_NUMBER;}
};



class ParseTokenERROR : public ParseTokenBase {
protected :
   std::string err;
public :
   ParseTokenERROR(const LexToken& ltoken , std::string error);
   
   inline std::string Error() {return err;}
   inline override ParserType() {return PARSE_ERROR;}
};



/// ParseToken allows us to wrap the different types of ParseTokens into a single type
class ParseToken {
protected :
   std::shared_ptr<ParseTokenBase> pbase;
public :
   
   LexToken LexerToken() {return pbase->LexerToken();}

   PARSE_TYPE ParserType() {return pbase->ParserType();}
};


typedef ParseToken (*PARSEFUNC)(LexToken);

ParseToken ParseWS(LexToken token);


/// Parsing functions
ParseToken ParseNUM(LexToken token);


/*
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
*/
const extern PARSEFUNC parser_funcs[NUM_LEXER_STATES];

#endif // Parser2_HPP

