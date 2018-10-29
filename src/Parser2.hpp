/**
   Parser2.hpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/14/2018
   Modified : 09/18/2018
   
   Parser2.hpp contains the interface for the parser.
*/


#ifndef Parser2_HPP
#define Parser2_HPP


#include <memory>
#include <vector>

#include "Lexer2.hpp"
#include "Data.hpp"



enum PARSE_TYPE {
   PARSE_WS         = 0,
   PARSE_KEYWORD    = 1,
   PARSE_IDENTIFIER = 2,
   PARSE_STRING     = 3,
   PARSE_NUMBER     = 4,
   PARSE_BLOCK      = 5,
   PARSE_OPERATOR   = 6,
   PARSE_ERROR      = 7,
   NUM_PARSE_TYPES  = 8
};



/// ParseTokenBase is a base class, extended to store specific information on Lexical words, rather than trying to
/// mash all the data into a single union or class

class ParseTokenBase {
protected :
   LexToken lextoken;
public :
   ParseTokenBase(const LexToken& token) : lextoken(token) {}
   
   virtual ~ParseTokenBase() {}
   
   LexToken LexerToken() const {return lextoken;}
   
   virtual PARSE_TYPE ParserType() const =0;

   virtual std::string MakeTag() const =0;
   
};



/** Classes derived from ParseTokenBase */



class ParseTokenWS : public ParseTokenBase {
public :
   ParseTokenWS(const LexToken& token);

   inline PARSE_TYPE ParserType() const override {return PARSE_WS;}

   virtual std::string MakeTag() const override;
};



class ParseTokenKEYWORD : public ParseTokenBase {
   KEYWORD_GROUP kwgroup;
   KEYWORD_TYPE kwtype;
public :
   ParseTokenKEYWORD(const LexToken& ltoken , KEYWORD_GROUP group , KEYWORD_TYPE type);
   
   KEYWORD_GROUP Group() {return kwgroup;}
   KEYWORD_TYPE WordType() {return kwtype;}
   inline PARSE_TYPE ParserType() const override {return PARSE_KEYWORD;}

   virtual std::string MakeTag() const override;
};



class ParseTokenID : public ParseTokenBase {
public :
   ParseTokenID(const LexToken& ltoken);

   inline PARSE_TYPE ParserType() const override {return PARSE_IDENTIFIER;}

   virtual std::string MakeTag() const override ;
};



class ParseTokenSTR : public ParseTokenBase {
public :
   ParseTokenSTR(const LexToken& ltoken);

   inline PARSE_TYPE ParserType() const override {return PARSE_STRING;}

   virtual std::string MakeTag() const override ;
};



class ParseTokenNUM : public  ParseTokenBase {
protected :
   unsigned short base;
   KString val;
   int dval;
public :
   ParseTokenNUM(const LexToken& ltoken , unsigned short numbase , KString numval);
      
   inline unsigned short Base() const {return base;}
   inline KString KStrValue()   const {return val;}
   inline int DecimalValue()    const {return dval;}
   
   inline PARSE_TYPE ParserType() const override {return PARSE_NUMBER;}

   virtual std::string MakeTag() const override ;
};



class ParseTokenBLOCK : public ParseTokenBase {
   KChar kchar;
public :
   ParseTokenBLOCK(const LexToken& ltoken , const KChar& kc);
   
   KChar BlockChar() {return kchar;}
   bool MatchesBlockChar(const KChar& kc);
   bool IsOpenBlock();
   bool IsCloseBlock();
   
   inline PARSE_TYPE ParserType() const override {return PARSE_BLOCK;}

   virtual std::string MakeTag() const override ;
};



class ParseTokenOP : public ParseTokenBase {
   OPNUM op;
public :
   ParseTokenOP(const LexToken& ltoken , OPNUM opnum);

   inline PARSE_TYPE ParserType() const override {return PARSE_OPERATOR;}
   inline OPNUM Op() {return op;}

   virtual std::string MakeTag() const override ;
};




class ParseTokenERROR : public ParseTokenBase {
protected :
   std::string err;
public :
   ParseTokenERROR(const LexToken& ltoken , std::string error);
   
   inline std::string Error() {return err;}
   inline PARSE_TYPE ParserType() const override {return PARSE_ERROR;}

   virtual std::string MakeTag() const override ;
};



/// ParseToken allows us to wrap the different types of ParseTokens into a single type
class ParseToken {
protected :
   std::shared_ptr<ParseTokenBase> pbase;
public :
   
   ParseToken(ParseTokenBase* base);
   
   LexToken LexerToken() const {return pbase->LexerToken();}

   inline PARSE_TYPE ParserType() {return pbase->ParserType();}

   inline ParseTokenBase* get() {return pbase.get();}
   inline const ParseTokenBase* get() const {return pbase.get();}
   
   std::string MakeTag() const;
   
   /// Flatten the interface
   ParseTokenKEYWORD* GetKeywordToken();
   ParseTokenID* GetIDToken();
   ParseTokenSTR* GetStringToken();
   ParseTokenNUM* GetNumToken();
   ParseTokenBLOCK* GetBlockToken();
   ParseTokenOP* GetOpToken();
   
   bool IsKeyword();
   bool IsID();
   bool IsString();
   bool IsNum();
   bool IsBlock();
   bool IsOpenBlock();
   bool IsCloseBlock();
   bool IsOp();
   
   KString GetKeyword();
   KString GetID();
   KString GetString();

   KEYWORD_GROUP GetKeywordGroup();
   KEYWORD_TYPE GetKeywordType();

   int GetNum();
   OPNUM GetOp();
};

class Parser {
protected :
   std::vector<ParseToken> ptokens;


public :
   
   inline void Clear() {ptokens.clear();}
   
   void Parse(const std::vector<LexToken>& ltokens);

   void WriteTags(std::ostream& os);
   
   
};



typedef ParseToken (*PARSEFUNC)(const LexToken& ltoken);

const extern PARSEFUNC parser_funcs[NUM_LEXER_STATES];

ParseToken ParseWS(const LexToken& ltoken);
ParseToken ParseID(const LexToken& ltoken);
ParseToken ParseSTR(const LexToken& ltoken);
ParseToken ParseNUM(const LexToken& ltoken);
ParseToken ParseBLOCK(const LexToken& ltoken);
ParseToken ParseOP(const LexToken& ltoken);
ParseToken ParseCMT(const LexToken& ltoken);
///ParseToken ParseERROR(const LexToken& ltoken);



#endif // Parser2_HPP

