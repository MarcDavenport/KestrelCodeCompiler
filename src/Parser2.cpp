


#include <sstream>



#include "Parser2.hpp"

#include "Exception.hpp"
#include "ParseUtils.hpp"

#include "Utility.hpp"
#include "Data.hpp"


ParseTokenWS::ParseTokenWS(const LexToken& token) :
      ParseTokenBase(token)
{
   /// WS is unused
   /// Sanity check
   EAGLE_ASSERT(token.Type() == LEX_WS);
}



std::string ParseTokenWS::MakeTag() const {
   std::stringstream ss("");
   ss << "<WS>";
   KString word = LexerToken().Word();
   if (word.Contains('\n')) {
      ss << '\n';
   }
   return ss.str();
}



ParseTokenKEYWORD::ParseTokenKEYWORD(const LexToken& ltoken , KEYWORD_GROUP group , KEYWORD_TYPE type) :
      ParseTokenBase(ltoken),
      kwgroup(group),
      kwtype(type)
{}



std::string ParseTokenKEYWORD::MakeTag() const {
   std::stringstream ss("");
   ss << "<" << KWStr(kwtype) << ">";
   return ss.str();
}



ParseTokenID::ParseTokenID(const LexToken& ltoken) :
      ParseTokenBase(ltoken)
{}



std::string ParseTokenID::MakeTag() const {
   std::stringstream ss("");
   ss << "<ID=" << LexerToken().Word() << ">";
   return ss.str();
}



ParseTokenSTR::ParseTokenSTR(const LexToken& ltoken) :
      ParseTokenBase(ltoken)
{}



std::string ParseTokenSTR::MakeTag() const {
   std::stringstream ss("");
   ss << "<STR=" << LexerToken().Word() << ">";
   return ss.str();
}



ParseTokenNUM::ParseTokenNUM(const LexToken& ltoken , unsigned short numbase , KString numval) :
      ParseTokenBase(ltoken),
      base(numbase),
      val(numval),
      dval(-1)
{
   EAGLE_ASSERT(ltoken.Type() == LEX_NUM);
   dval = CrockfordToDecimal(base , val);
}



std::string ParseTokenNUM::MakeTag() const {
   std::stringstream ss("");
   ss << "<NUM=" << val << "_" << base << ">";
   return ss.str();
}



ParseTokenBLOCK::ParseTokenBLOCK(const LexToken& ltoken , const KChar& kc) :
      ParseTokenBase(ltoken),
      kchar(kc)
{}



bool ParseTokenBLOCK::MatchesBlockChar(const KChar& kc) {
   switch (kchar) {
      case '(' : return kc == ')';break;
      case '{' : return kc == '}';break;
      case '[' : return kc == ']';break;
      case ')' : return kc == '(';break;
      case '}' : return kc == '{';break;
      case ']' : return kc == '[';break;
      default : return false;break;
   };
   return false;
}



std::string ParseTokenBLOCK::MakeTag() const {
   std::stringstream ss("");
   ss << "<BLK='" << LexerToken().Word() << ">";
   return ss.str();
}



ParseTokenOP::ParseTokenOP(const LexToken& ltoken , OPNUM opnum) :
      ParseTokenBase(ltoken),
      op(opnum)
{}



std::string ParseTokenOP::MakeTag() const {
   std::stringstream ss("");
   ss << "<" << OpStr(op) << ">";
   return ss.str();
}



ParseTokenERROR::ParseTokenERROR(const LexToken& ltoken , std::string error) :
      ParseTokenBase(ltoken),
      err(error)
{
   fprintf(stdout , "Parse error on line %d column %d : %s\n" , lextoken.Line() , lextoken.Column() , err.c_str());
#ifdef STRICT_ERRORS
   throw Exception(err);/// TODO : 
#endif
}



std::string ParseTokenERROR::MakeTag() const {
   return "<PARSE_ERROR?>";
}



/// -----------------     ParseToken class     -----------------------



ParseToken::ParseToken(ParseTokenBase* base) :
      pbase(base)
{}



std::string ParseToken::MakeTag() const {
   return get()->MakeTag();
}



/// --------------------------     Parser class     ----------------------



void Parser::Parse(const std::vector<LexToken>& ltokens) {
   Clear();
   
   auto it = ltokens.begin();
   while (it != ltokens.end()) {
      /// We can optionally filter whitespace and comments here, and we ignore lex errors
      const LexToken& token = *it;
      if (token.Type() == LEX_ERROR || token.Type() == LEX_COMMENT) {
         ++it;
         continue;
      }
      ptokens.push_back(parser_funcs[token.Type()](token));
      ++it;
   }
}



void Parser::WriteTags(std::ostream& os) {
   auto it = ptokens.begin();
   for (const auto& ptoken : ptokens) {
      os << ptoken.MakeTag();/// No newline here, WS has been preserved
   }
}



/// Global functions and data


/**

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

*/

ParseToken ParseWS(const LexToken& token) {
   return ParseToken(new ParseTokenWS(token));/// Pass whitespace on?
}



ParseToken ParseID(const LexToken& ltoken) {
   /// Basically this function filters out the keywords and makes everything else an identifier, type to be
   /// determined in Stage 2
   KEYWORD_TYPE type = NUM_KEYWORDS;
   /// Sanity check
   EAGLE_ASSERT(ltoken.Type() == LEX_ID);
   
   /// May be reserved word, which consists of control commands, and...TODO
   auto it = reserved_words.begin();
   int i = 0 , index = -1;
   while (it != reserved_words.end()) {
      if (ltoken.Word() == *it) {
         index = i;
         break;
      }
      ++i;
      ++it;
   }
   if (index != -1) {
      type = (KEYWORD_TYPE)index;
   }

   if (it != reserved_words.end()) {

      KEYWORD_GROUP group = NUM_KEYWORD_GROUPS;
      bool found = false;
      
      for (unsigned int i = 0 ; i < NUM_KEYWORD_GROUPS ; ++i) {
         const std::unordered_set<KString>& wset = reserved_word_sets[i];
         std::unordered_set<KString>::const_iterator it = wset.find(ltoken.Word());
         if (it != wset.end()) {
            found = true;
            group = (KEYWORD_GROUP)i;
            break;
         }
      }

      if (found) {
         return ParseToken(new ParseTokenKEYWORD(ltoken , group , type));
      }

      EAGLE_ASSERT(found);
      throw Exception("ParseID : Found reserved word, but group is unknown!");

   }
   /// May be function or object, but we haven't parsed function or object definitions yet so we wouldn't know
   /// An identifier would either be an object, or the name of a function or procedure, we'll find out in a later stage
   return ParseToken(new ParseTokenID(ltoken));
}



ParseToken ParseSTR(const LexToken& ltoken) {
   /// Sanity check
   EAGLE_ASSERT(ltoken.Type() == LEX_STR);
   /// This function is dumb, it just passes the KString stored inside the LexToken on
   return ParseToken(new ParseTokenSTR(ltoken));
}



ParseToken ParseNUM(const LexToken& token) {
   const KString& w = token.Word();
   if (w.Find('#') == w.End()) {/// This is a regular base 10 number, no # sign or extended digits
      return ParseToken(new ParseTokenNUM(token , 10 , w));/// base is our number, no value was specified
   }
   KString basestr(w.Begin()     , w.Find('#'));
   KString numstr (w.Find('#')++ , w.End()    );
   
   short base = CrockfordToDecimal(10 , basestr);
   
   return ParseToken(new ParseTokenNUM(token , base , numstr));
}




ParseToken ParseBLOCK(const LexToken& ltoken) {
   const KString& w = ltoken.Word();
   if (w.Size() != 1) {
      /// Lexer messed up
      EAGLE_ASSERT(w.Size() == 1);
      return ParseToken(new ParseTokenERROR(ltoken , StringPrintF("Unexpected block size of %d KChars" , (int)w.Size())));
   }
   KChar kc = w[0];
   if ((block_openset.find(kc) == block_openset.end()) &&
       block_closeset.find(kc) == block_closeset.end()) 
   {
      return ParseToken(new ParseTokenERROR(ltoken , StringPrintF("ParseBLOCK reports an invalid character '%c'" , kc)));
   }
   return ParseToken(new ParseTokenBLOCK(ltoken , kc));
}



ParseToken ParseOP(const LexToken& ltoken) {
   bool found = operator_set.find(ltoken.Word()) != operator_set.end();
   if (!found) {
      std::stringstream sstrm;
      sstrm << "ParseOP reports an invalid op! (" << ltoken.Word() << ")";
      return ParseToken(new ParseTokenERROR(ltoken , sstrm.str()));
   }
   
   OPNUM op = GetOp(ltoken.Word());
   return ParseToken(new ParseTokenOP(ltoken , op));/// TODO : FIXME
}






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



const PARSEFUNC parser_funcs[NUM_LEXER_STATES] = {
   ParseWS,
   ParseID,
   ParseSTR,
   ParseNUM,
   ParseBLOCK,
   ParseOP,
   0,        ///   ParseCMT,
   0         ///   ParseError
};

