



#ifndef Lexer1_HPP
#define Lexer1_HPP

#error DEPRECATED HEADER

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_set>



enum LEXER_STATE_TYPE {
   LS_START        = 0,
   LS_WHITESPACE   = 1,
   LS_IDENTIFIER   = 2,
   LS_QUOTEDSTRING = 3,
   LS_NUMBER       = 4,
   LS_OBLOCK       = 5,
   LS_CBLOCK       = 6,
   LS_SEPARATOR    = 7,
   LS_OPERATOR     = 8,
   LS_STOP         = 9,
   LS_ERROR        = 10,
   NUM_LEXER_STATES = 11
};


std::string LexerStateTypeString(LEXER_STATE_TYPE t);

class Lexeme;

class LexemeBase {
protected :

   std::string word;

public :
   
   virtual ~LexemeBase() {}
   
   virtual LEXER_STATE_TYPE OurType()=0;

   virtual LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm)=0;
   
   void Clear() {word = "";}
   std::string Word() {return word;}
   
   void WriteTag(std::ostream& os);
};



class LexemeSTART : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_START;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeWS : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_WHITESPACE;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeID : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_IDENTIFIER;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeQSTR : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_QUOTEDSTRING;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeNUM : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_NUMBER;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeOBLOCK : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_OBLOCK;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeCBLOCK : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_CBLOCK;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeSEP : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_SEPARATOR;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeOP : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_OPERATOR;}
//   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
      (void)block_ref;
      (void)istrm;
      std::unordered_set<char> charset = {'!' , '+' , '-' , '*' , '/' , '<' , '>' , '~' , '&' , '|' , '^' , '$' , ':' , ';'};
      return LS_ERROR;
   }
};



class LexemeSTOP : public LexemeBase {
public :
   LEXER_STATE_TYPE OurType() {return LS_STOP;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};



class LexemeERR : public LexemeBase {
public :
   LexemeERR(std::string err) {word = err;}
   
   LEXER_STATE_TYPE OurType() {return LS_ERROR;}
   LEXER_STATE_TYPE ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm);
};






class Lexeme {
   std::shared_ptr<LexemeBase> lexbase;
public :
   Lexeme(LexemeBase* b) : lexbase(b) {}
   
   LexemeBase* operator->() {return lexbase.get();}
   LexemeBase& operator*() {return *(lexbase.get());}
};



class Lexer {
   
   std::vector<Lexeme> blocks;
   
public :
   
   void Clear();

   void Lexify(std::istream& istrm);

   void WriteTags(std::ostream& os);
};



#endif // Lexer1_HPP
