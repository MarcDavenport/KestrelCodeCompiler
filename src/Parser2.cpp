


#include <sstream>



#include "Parser2.hpp"

#include "Exception.hpp"
#include "ParseUtils.hpp"

#include "Utility.hpp"



ParseTokenWS::ParseTokenWS(const LexToken& token) :
      ParseTokenBase(token)
{
   /// WS is unused
   /// Sanity check
   EAGLE_ASSERT(token.Type() == LEX_WS);
}



ParseTokenKEYWORD::ParseTokenKEYWORD(const LexToken& ltoken , KEYWORD_GROUP group) :
      ParseTokenBase(ltoken),
      kwgroup(group)
{}



ParseTokenID::ParseTokenID(const LexToken& ltoken) :
      ParseTokenBase(ltoken)
{}



ParseTokenSTR::ParseTokenSTR(const LexToken& ltoken) :
      ParseTokenBase(ltoken)
{}



ParseTokenNUM::ParseTokenNUM(const LexToken& ltoken , unsigned short numbase , KString numval) :
      ParseTokenBase(ltoken),
      base(numbase),
      val(numval),
      dval(-1)
{
   EAGLE_ASSERT(ltoken.Type() == LEX_NUM);
   dval = CrockfordToDecimal(base , val);
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



ParseTokenOP::ParseTokenOP(const LexToken& ltoken , OPCLASS opc) :
      ParseTokenBase(ltoken),
      opclass(opc)
{}



ParseTokenERROR::ParseTokenERROR(const LexToken& ltoken , std::string error) :
      ParseTokenBase(ltoken),
      err(error)
{
   fprintf(stdout , "Parse error on line %d column %d : %s\n" , lextoken.Line() , lextoken.Column() , err.c_str());
#ifdef STRICT_ERRORS
   throw Exception(err);/// TODO : 
#endif
}



/// -----------------     ParseToken class     -----------------------



ParseToken::ParseToken(ParseTokenBase* base) :
      pbase(base)
{}



/// --------------------------     Parser class     ----------------------



void Parser::Parse(const std::vector<LexToken>& ltokens) {
   Clear();
   
   for (unsigned int i = 0 ; i < ltokens.size() ; ++i) {
      /// First, remove all whitespace and comments, as the parser doesn't use them
      const LexToken& token = ltokens[i];
      if (token.Type() == LEX_COMMENT || token.Type() == LEX_ERROR) {
         continue;/// filter comments, and errors
      }
      ptokens.push_back(parser_funcs[token.Type()](token));
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

/// TODO : Add reserved words to list
/// From kestrel definition :
const std::unordered_set<KString> reserved_words = {
   KString("const"),        /// various definitions
   KString("final"),
   KString("type"),
   KString("external"),     /// mark a function as external

   KString("var"),
   KString("procedure"),
   KString("function"),

   KString("private"),      /// makes a definition as private
   KString("restricted"),   /// makes a definition visible in extensions


   KString("enum"),         /// various types
   KString("array"),
   KString("set"),
   KString("record"),
   KString("of"),

   KString("in"),

   KString("if"),           /// statement
   KString("then"),
   KString("else"),
   KString("end"),          /// terminates many constructs
   KString("select"),       /// statement
   KString("case"),
   KString("return"),       /// statement

   KString("while"),        /// statement
   KString("do"),
   KString("until"),
   KString("for"),          /// statement

   KString("exception"),
   KString("raise"),        /// statement
   KString("catch"),        /// statement

   KString("null")          /// a distinguished pointer value
};

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
const std::vector< std::unordered_set<KString> > reserved_word_sets = {
   /** KWG_MODIFIER */
   std::unordered_set<KString>({
      KString("const"),       /// various definitions
      KString("final"),
      KString("type"),
      KString("external")    /// mark a function as external
   }),
   /** KWG_DECLARATION */
   std::unordered_set<KString>({
      KString("var"),
      KString("procedure"),
      KString("function")
   }),
   /** KWG_ACCESS */
   std::unordered_set<KString>({
      KString("private"),     /// makes a definition as private
      KString("restricted")  /// makes a definition visible in extensions
   }),
   /** KWG_TYPE */
   std::unordered_set<KString>({
      KString("enum"),        /// various types
      KString("array"),
      KString("set"),
      KString("record"),
      KString("of")
   }),
   /** KWG_RANGE */
   std::unordered_set<KString>({
      KString("in")
   }),
   /** KWG_CONTROL */
   std::unordered_set<KString>({
      KString("if"),          /// statement
      KString("then"),
      KString("else"),
      KString("end"),         /// terminates many constructs
      KString("select"),      /// statement
      KString("case")
   }),
   /** KWG_LOOP */
   std::unordered_set<KString>({
      KString("while"),       /// statement
      KString("do"),
      KString("until"),
      KString("for")          /// statement
   }),
   /** KWG_EXCEPTION */
   std::unordered_set<KString>({
      KString("exception"),
      KString("raise"),       /// statement
      KString("catch"),       /// statement
      KString("return")       /// statement
   }),
   /** KWG_NULLPTR */
   std::unordered_set<KString>({
      KString("null")         /// a distinguished pointer value
   })
};



const std::unordered_set<KChar> block_openset = {'(' , '{' , '['};
const std::unordered_set<KChar> block_closeset = {')' , '}' , ']'};



const unsigned int MAX_NUM_OP_CHARS = 2;

const std::unordered_set<KString> operator_set2 = {
   KString(".."), ///subrange constructor
   KString("/="), ///comparison
   KString(">"),  ///comparison
   KString(">="), ///comparison
   KString("<"),  ///comparison
   KString("<=")  ///comparison 
};
const std::unordered_set<KString> operator_set1 = {
   KString(";"), ///statement terminator/separator
   KString("="), ///assignment and comparison
   KString(":"), ///definition
   KString(","), ///separating expressions 
   KString("@"), ///pointer definition and use

   KString("+"), ///arithmetic
   KString("-"), ///arithmetic (unary or binary)
   KString("*"), ///arithmetic
   KString("/"), ///arithmetic
   KString("%"), ///arithmetic (remainder)

   KString("&"), ///logic
   KString("|"), ///logic
   KString("~"), ///logical not or one's complement ()
   KString(".")  ///field selection
};

const std::unordered_set<KString> operator_set_math = {
   KString("*"), ///arithmetic
   KString("/"), ///arithmetic
   KString("%"), ///arithmetic (remainder)
   KString("+"), ///arithmetic
   KString("-")  ///arithmetic (unary or binary)
};

const std::unordered_set<KString> operator_set_logic = {
   KString("~"),  ///logical not or one's complement ()
   KString("&"),  ///logic
   KString("|"),  ///logic
   KString("/="), ///comparison
   KString(">"),  ///comparison
   KString(">="), ///comparison
   KString("<"),  ///comparison
   KString("<=")  ///comparison 
};


ParseToken ParseWS(const LexToken& token) {
   return ParseToken(new ParseTokenWS(token));/// Pass whitespace on?
}



ParseToken ParseID(const LexToken& ltoken) {/// TODO : IMPLEMENT ME
   /// Basically this function filters out the keywords and makes everything else an identifier, type to be
   /// determined in Stage 2
   
   /// Sanity check
   EAGLE_ASSERT(ltoken.Type() == LEX_ID);
   
   /// May be reserved word, which consists of control commands, and...TODO
   std::unordered_set<KString>::const_iterator it = reserved_words.find(ltoken.Word());
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
         return ParseToken(new ParseTokenKEYWORD(ltoken , group));
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
   bool found = operator_set2.find(ltoken.Word()) != operator_set2.end();
   if (!found) {
      found = operator_set1.find(ltoken.Word()) != operator_set1.end();
   }
   std::stringstream sstrm;
   sstrm << "ParseOP reports an invalid op! (" << ltoken.Word() << ")";
   if (!found) {
      return ParseToken(new ParseTokenERROR(ltoken , sstrm.str()));
   }
#warning FIXME I need to split ops into groups
   return ParseToken(new ParseTokenOP(ltoken , NUM_OP_CLASSES));/// TODO : FIXME
}







/** Not used
ParseToken ParseCMT(const LexToken& ltoken);
ParseToken ParseCMT(const LexToken& ltoken) {
   #error UNUSED
};
*/



/** Not used
ParseToken ParseERROR(const LexToken& ltoken) {
   #error UNUSED
}
*/


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
   0,           ///ParseCMT,
   0            /// ParseERROR
};

