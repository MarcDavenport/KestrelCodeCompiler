

#include "Lexer2.hpp"
#include "Exception.hpp"
#include "Utility.hpp"
#include "KString.hpp"
#include "Data.hpp"


#include <cassert>
#include <cstring>



void StreamFailed() {
   throw Exception("Stream failure detected.");
}


std::string LexerStateTypeString(LEX_TYPE t) {
   static const std::string strs[NUM_LEXER_STATES + 1] = {
      std::string("LEX_WS"),
      std::string("LEX_ID"),
      std::string("LEX_STR"),
      std::string("LEX_NUM"),
      std::string("LEX_BLOCK"),
      std::string("LEX_OP"),
      std::string("LEX_ERROR"),
      std::string("LEX_COMMENT"),
      std::string("NUM_LEXER_STATES")
   };
   return strs[t];
}





/** From Parser.cpp
const std::unordered_set<const char*> operator_set2 = {
   "..", ///subrange constructor
   "/=", ///comparison
   ">",  ///comparison
   ">=", ///comparison
   "<",  ///comparison
   "<=" ///comparison 
};
const std::unordered_set<const char*> operator_set1 = {
   ";", ///statement terminator/separator
   "=", ///assignment and comparison
   ":", ///definition
   ",", ///separating expressions 
   "@", ///pointer definition and use
   "+", ///arithmetic
   "-", ///arithmetic (unary or binary)
   "*", ///arithmetic
   "/", ///arithmetic
   "%", ///arithmetic (remainder)
   "&", ///logic
   "|", ///logic
   "~", ///logical not or one's complement ()
   "."  ///field selection
};
*/




LexToken::LexToken(LEX_TYPE t) :
      type(t),
      line(-1),
      word("")
{}



LexToken::LexToken(LEX_TYPE t , const KString& s) :
      type(t),
      line(-1),
      word(s)
{}




void LexToken::Clear() {
   line = -1;
   word.Clear();
}


/** TODO : REMOVE unused
int LexToken::CountNewlines() {
   int count = 0;
   for (unsigned int i = 0 ; i < word.size() ; ++i) {
      if (word[i] == '\n') {count++;}
   }
   return count;
}
*/


LexToken LexWS(std::istream& in) {
   LexToken token(LEX_WS);
   while (in.good() && !in.eof()) {
      char c = in.peek();
      if (isspace(c)) {
         token.PushBack(in.get());
         /// HAHAHA QUICK AND DIRTY HACK TO PRESERVE NEWLINES, now all ws will be split by newlines
         if (c == '\n') {
            return token;
         }
         if (!in.good() && !in.eof()) {
            StreamFailed();
         }
      }
      else {
         return token;
      }
   }
   return LexToken(LEX_ERROR , "Unexpected error in LexWS???");
}



LexToken LexID(std::istream& in) {

   LexToken token(LEX_ID);
   
   if (in.good()) {
      char c = in.peek();
      EAGLE_ASSERT(isalpha(c));
      while (isalpha(c) || isdigit(c)) {
         token.PushBack(in.get());
         c = in.peek();
         if (!in.good()) {
            StreamFailed();
         }
      }
   }
   return token;
}



LexToken LexSTR(std::istream& in) {
   LexToken token(LEX_STR);
   
   if (in.good()) {
      char c = in.peek();
      EAGLE_ASSERT(c == '\"' || c == '\'');
      char qtype = c;
      do {
         token.PushBack(in.get());
         if (!in.good()) {
            StreamFailed();
            goto error;
         }
         c = in.peek();
         if (c == EOF) {
            return LexToken(LEX_ERROR , "Unexpected EOF. Expected closing quote.");
         }
      } while (c != qtype);
      token.PushBack(in.get());
      return token;
   }
   StreamFailed();
   error:
   return LexToken(LEX_ERROR , "Bad Stream");
}



LexToken LexNUM(std::istream& in) {
   char c = in.peek();
   if (!isdigit(c)) {
      EAGLE_ASSERT(isdigit(c));
      return LexToken(LEX_ERROR , "Expected number.");
   }

   LexToken token(LEX_NUM);
   while (isdigit(c)) {
      token.PushBack(in.get());
      if (!in.good()) {
         StreamFailed();
         goto error;
      }
      if (in.eof()) {
         return token;
      }
      c = in.peek();
   }
   if (c == '#') {
      token.PushBack(in.get());
      if (!in.good()) {
         StreamFailed();
         goto error;
      }
      c = in.peek();
      while (isdigit(c)) {
         token.PushBack(in.get());
         if (!in.good()) {
            StreamFailed();
            goto error;
         }
         if (in.eof()) {
            return token;
         }
         c = in.peek();
      }
   }
   return token;
   error:
   return LexToken(LEX_ERROR , "Bad Stream.");
}



LexToken LexBLOCK(std::istream& in) {

   LexToken token(LEX_BLOCK);
   bool found = false;
   
   char c = in.peek();
   if ((found = (blockchars.find(c) != blockchars.end()))) {
      token.PushBack(in.get());
      return token;
   }
   return LexToken(LEX_ERROR , "Expected block char.");
}


/** TODO : (LEXER) With operators, what about edge cases like a = -b? It could be written as a=-b without spaces */

LexToken LexOP(std::istream& in) {
   LexToken token(LEX_OP);
   
   int ccount = 0;
   while (in.good() && !in.eof() && ccount < 2) {
      if (opchars.find(in.peek()) != opchars.end()) {
         token.PushBack(in.get());
         ++ccount;
      }
      else {
         break;/// Op char not found
      }
   }
   if (0 == token.Word().Size()) {
      if (!in.good() && !in.eof()) {
         StreamFailed();
         return LexToken(LEX_ERROR , KString("Bad stream"));
      }
      else if (in.eof()) {
         return LexToken(LEX_ERROR , KString("Unexpected EOF encountered during LexOP"));
      }
      else {
         return LexToken(LEX_ERROR , KString("LexOP reports op char not found!"));
      }
   }
   return token;
}



LexToken LexCMT(std::istream& in) {
   LexToken token(LEX_COMMENT);
   
   char c = '\0';
   do {
      c = in.peek();
      if (c != '\n') {
         token.PushBack(in.get());
      }
   } while (in.good() && !in.eof() && c != '\n');
   if (!in.good()) {
      StreamFailed();
   }
   if (in.eof()) {
      return LexToken(LEX_ERROR , "Unexpected EOF in LexCMT");
   }
   return token;
}



LexToken LexERR(std::istream& in) {
   return LexToken(LEX_ERROR , StringPrintF("Unexpected character '%c'." , in.get()));
}



const LEXFUNC Lexer2::lexfuncs[NUM_LEXER_STATES] = {
   LexWS,
   LexID,
   LexSTR,
   LexNUM,
   LexBLOCK,
   LexOP,
   LexCMT,
   LexERR
};



KString Lexer2::MakeTag(const LexToken& token) {
   static const std::string tagnames[NUM_LEXER_STATES] = {
      std::string("WS"),
      std::string("ID"),
      std::string("STR"),
      std::string("NUM"),
      std::string("BLK"),
      std::string("OP"),
      std::string("CMT"),
      std::string("ERR")
   };
   KString tag("<");
   KString value = token.Word();
   int i = 0;
   int nlcount = 0;
   /// Strip newlines so they don't mess with our formatting
   while (i < (int)value.Size()) {
      if (value[i] == '\n') {
         nlcount++;
      }
      else {
         tag.PushBack(value[i]);
      }
      ++i;
   }
   tag.PushBack('>');
///   std::string tag = StringPrintF("<%s = '%s'>" , tagnames[token.Type()].c_str() , value.c_str());
///   std::string tag = StringPrintF("<%s>%s" , tagnames[token.Type()].c_str() , value.c_str());
   /// Add the newlines back in at the end so it displays correctly
   while (nlcount) {
      --nlcount;
      tag.PushBack('\n');
   }
   return tag;
}



Lexer2::Lexer2() :
      tokens()
{}



LEX_TYPE Lexer2::LexerState(char c) {
   
   static LEX_TYPE state_table[128] = {};
   
   static int ready = 0;
   if (ready) {
      if (c < 0)/** || ch > 127) */{return LEX_ERROR;}
      return state_table[(int)c];
   }
   else {
      /// Build the lexer state table
      for (char ch = 0 ; ; ++ch) {
         int i = ch;
         if      (isspace(ch))                             {state_table[i] = LEX_WS;}
         else if (isalpha(ch))                             {state_table[i] = LEX_ID;}
         else if (isdigit(ch))                             {state_table[i] = LEX_NUM;}
         else if (quotechars.find(ch) != quotechars.end()) {state_table[i] = LEX_STR;}
         else if (blockchars.find(ch) != blockchars.end()) {state_table[i] = LEX_BLOCK;}
         else if (opchars.find(ch) != opchars.end())       {state_table[i] = LEX_OP;}
         else                                              {state_table[i] = LEX_ERROR;}
         if (ch == 127) {break;}
      }
      ready = 1;
      return LexerState(c);
   }
   return LEX_ERROR;
}



void Lexer2::Lexify(std::istream& istrm) {

   LEX_TYPE state = LEX_ERROR;
   
   int line = 1;
   int column = 0;
   
   while (istrm.good() && !istrm.eof()) {
      int c = istrm.peek();
      if (c == EOF) {break;}
      
      if (c == '\0') {
         throw Exception(StringPrintF(
            "Embedded NULL char! On line %d at column %d\n. Are you sure this file isn't binary?\n" , line , column
         ));
      }
      
      state = LexerState(c);

      if (c == '-') {
         /// Possible comment
         istrm.get();
         if (istrm.peek() == '-') {
            state = LEX_COMMENT;
         }
         EAGLE_ASSERT(istrm.unget());
      }
      
      LexToken token = lexfuncs[state](istrm);
      
      token.SetLine(line);
      token.SetColumn(column);
      
      EAGLE_ASSERT(token.Word().Size());
      
      std::cout << token.Word();
      
      tokens.push_back(token);
      
      if (token.Type() == LEX_ERROR) {
         std::cout << "ERROR : " << token.Word() << "on line " << line << " column " << column << std::endl;
         EAGLE_ASSERT(istrm.good() && !istrm.eof());
      }
      
      KString word = token.Word();
      for (unsigned int i = 0 ; i < word.Size() ; ++i) {
         if (word[i] == '\n') {++line;column = 0;} else {++column;}
      }

      if (!istrm.good() && !istrm.eof()) {
         StreamFailed();
      }
   }
}



void Lexer2::WriteTags(std::ostream& os) {
   os << "Kestrel Lexifier Tag format :" << std::endl;
   for (unsigned int i = 0 ; i < tokens.size() ; ++i) {
      os << MakeTag(tokens[i]);/// Our tags take care of newlines
   }
   os << std::endl;
}



void Lexer2::DumpStateTable(std::ostream& os) {
   os << "Dumping Lexer State Table :" << std::endl;
   for (char c = -128 ; ; ++c) {
      LEX_TYPE type = LexerState(c);
      std::string typestr = LexerStateTypeString(type);
      os << StringPrintF("%d\t%c\t%s\n" , (int)c , c , typestr.c_str());
      if (c == 127) {break;}
   }
   os << std::endl;
}















