






#include "Lexer1.hpp"

#include <cassert>

/// -----------------      Global functions     ----------------------





std::string LexerStateTypeString(LEXER_STATE_TYPE t) {
   static const char* lstrs[NUM_LEXER_STATES] = {
      "LS_START",
      "LS_WHITESPACE",
      "LS_IDENTIFIER",
      "LS_QUOTEDSTRING",
      "LS_NUMBER",
      "LS_OBLOCK",
      "LS_CBLOCK",
      "LS_SEPARATOR",
      "LS_OPERATOR",
      "LS_STOP",
      "LS_ERROR"
   };
   return lstrs[t];
}



/// ---------------------     LexemeBase     -------------------------------



void LexemeBase::WriteTag(std::ostream& os) {
   os << "<" << LexerStateTypeString(OurType()) << ">";
}

   
   
/// ----------------------      Lexeme sub classes    -------------------------



LEXER_STATE_TYPE LexemeSTART::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();

   (void)block_ref;
   
   /// TODO : THIS SUCKS
   if (istrm.good()) {
      int c = istrm.peek();
      if (isspace(c)) {
         return LS_WHITESPACE;
      }
      else if (isdigit(c)) {
         return LS_NUMBER;
      }
      else if (isalpha(c)) {
         return LS_IDENTIFIER;
      }
      else if (c == '\"' || c == '\'') {
         return LS_QUOTEDSTRING;
      }
      else if (c == '{' || c == '[' || c == '(') {
         return LS_OBLOCK;
      }
      else if (c == '}' || c == ']' || c == ')') {
         return LS_CBLOCK;
      }
      else if (c == ',') {
         return LS_SEPARATOR;
      }
      else if (c == EOF) {
         return LS_STOP;
      }
      else {
         return LS_ERROR;
      }
   }
   return LS_ERROR;
}



LEXER_STATE_TYPE LexemeWS::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   
   while (istrm.good() && !istrm.eof()) {
      char c = istrm.peek();
      if (isspace(c)) {
         word.push_back(istrm.get());
      }
      else {
         block_ref->push_back(Lexeme(new LexemeWS(*this)));
         return LS_START;
      }
   }
   return LS_ERROR;
}



LEXER_STATE_TYPE LexemeID::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   
   if (istrm.eof()) {
      return LS_ERROR;
   }
   if (istrm.good()) {
      char c = istrm.peek();
      assert(isalpha(c));
      while (isalpha(c) || isdigit(c)) {
         word.push_back(istrm.get());
         c = istrm.peek();
      }
      block_ref->push_back(Lexeme(new LexemeID(*this)));
      return LS_START;
   }
   return LS_ERROR;
}



LEXER_STATE_TYPE LexemeQSTR::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   
   if (istrm.good()) {
      char c = istrm.peek();
      assert(c == '\"' || c == '\'');
      char qtype = c;
      do {
         word.push_back(istrm.get());
         if (!istrm.good()) {
            goto error;
         }
         c = istrm.peek();
         if (c == EOF) {
            block_ref->push_back(Lexeme(new LexemeERR("Expected closing quote")));
            return LS_ERROR;
         }
      } while (c != qtype);
      word.push_back(istrm.get());
      block_ref->push_back(Lexeme(new LexemeQSTR(*this)));
      return LS_START;
   }
   error:
   block_ref->push_back(Lexeme(new LexemeERR("Bad Stream")));
   return LS_ERROR;
}



LEXER_STATE_TYPE LexemeNUM::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   
   char c = istrm.peek();
   if (!isdigit(c)) {
      block_ref->push_back(Lexeme(new LexemeERR("Expected number.")));
      return LS_ERROR;
   }
   assert(isdigit(c));

   while (isdigit(c)) {
      word.push_back(istrm.get());
      if (!istrm.good()) {
         goto error;
      }
      c = istrm.peek();
   }
   if (c == '#') {
      word.push_back(istrm.get());
      if (!istrm.good()) {
         goto error;
      }
      c = istrm.peek();
      while (isdigit(c)) {
         word.push_back(istrm.get());
         if (!istrm.good()) {
            goto error;
         }
         c = istrm.peek();
      }
   }
   block_ref->push_back(Lexeme(new LexemeNUM(*this)));
   return LS_START;
   
   error:
   block_ref->push_back(Lexeme(new LexemeERR("Bad Stream.")));
   return LS_ERROR;
}



LEXER_STATE_TYPE LexemeOBLOCK::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   
   char c = istrm.peek();
   assert((c == '{') || (c == '[') || (c == '('));
   word.push_back(istrm.get());
   block_ref->push_back(Lexeme(new LexemeOBLOCK(*this)));
   return LS_START;
   /// How to deal with nested blocks? - Don't
}



LEXER_STATE_TYPE LexemeCBLOCK::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   
   char c = istrm.peek();
   assert((c == '}') || (c == ']') || (c == ')'));
   word.push_back(istrm.get());
   block_ref->push_back(Lexeme(new LexemeCBLOCK(*this)));
   return LS_START;
   /// How to deal with nested blocks? - Don't
}



LEXER_STATE_TYPE LexemeSEP::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   
   char c = istrm.peek();
   assert(c == ',');
   word.push_back(istrm.get());
   block_ref->push_back(Lexeme(new LexemeSEP(*this)));
   return LS_START;
}



LEXER_STATE_TYPE LexemeSTOP::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   Clear();
   char c = istrm.peek();
   assert(c == EOF);
   word.push_back(EOF);
   block_ref->push_back(Lexeme(new LexemeSTOP(*this)));
   return LS_STOP;
}



LEXER_STATE_TYPE LexemeERR::ConsumeInput(std::vector<Lexeme>* block_ref , std::istream& istrm) {
   (void)block_ref;
   (void)istrm;
   return LS_START;
}



/// -----------------------      Lexeme      ------------------------




/// -----------------------     Lexer       ----------------------------




void Lexer::Clear() {
   blocks.clear();
}



void Lexer::Lexify(std::istream& istrm) {
   Clear();
   Lexeme lexers[NUM_LEXER_STATES] = {
      Lexeme(new LexemeSTART()),
      Lexeme(new LexemeWS()),
      Lexeme(new LexemeID()),
      Lexeme(new LexemeQSTR()),
      Lexeme(new LexemeNUM()),
      Lexeme(new LexemeOBLOCK()),
      Lexeme(new LexemeCBLOCK()),
      Lexeme(new LexemeSEP()),
      Lexeme(new LexemeOP()),
      Lexeme(new LexemeSTOP()),
      Lexeme(new LexemeERR(""))
   };
   LEXER_STATE_TYPE state = LS_START;
   int line = 0;
   while (istrm.good() && !istrm.eof()) {
      char c = istrm.peek();
      if (c == '\n') {
         ++line;
      }
      Lexeme& lex = lexers[state];
      state = lex->ConsumeInput(&blocks , istrm);
      if (state == LS_ERROR) {
         std::cout << "<LS_ERROR (" << lex->Word() << ") : Line #>" << line << std::endl;
      }
      if (state == LS_STOP) {
         lex->ConsumeInput(&blocks , istrm);
         break;
      }
   }
   for (int i = 0 ; i < NUM_LEXER_STATES ; ++i) {
///      delete lexers[i];/// We don't actually need to do anything, as the Lexeme class will dispose of the contents automagically
   }
}



void Lexer::WriteTags(std::ostream& os) {
   for (int i = 0 ; i < (int)blocks.size() ; ++i) {
      Lexeme& l = blocks[i];
      l->WriteTag(os);
//** Render new lines
      if (l->OurType() == LS_WHITESPACE) {
         std::string word = l->Word();
         for (int j = 0 ; j < (int)word.size() ; ++j) {
            if (word[j] == '\n') {
               os << std::endl;
            }
         }
      }
//*/
   }
}









