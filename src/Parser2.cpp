



#include "Parser2.hpp"




ParseTokenWS::ParseTokenWS(const LexToken& token) :
      ParseTokenBase(token)
{
   /** WS is unused */
   /// Sanity check
   EAGLE_ASSERT(token.Type() == LEX_WS);
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



ParseTokenERROR::ParseTokenERROR(const LexToken& ltoken , std::string error) :
      ParseTokenBase(ltoken),
      err(error)
{
   fprintf(stdout , "Parse error on line %d column %d : %s\n" , lextoken.Line() , lextoken.Column() , err.c_str());
#ifdef STRICT_ERRORS
   throw Exception(err);/// TODO : 
#endif
}



/// Global functions



ParseToken ParseWS(LexToken token) {
   return ParseToken(new ParseWS(token))
}



ParseToken ParseNUM(LexToken token) {
   std::string w = token.Word();
   int base = 10;
   char nbuf[MAX_NUMSTR_LENGTH] = {0};
   if (w.find('#') == std::string::npos) {/// This is a regular base 10 number, no # sign or extended digits
      return ParseToken(new ParseTokenNUM(token , 10 , KString(w.c_str()));/// base is our number, no value was specified
   }
   if (2 == sscanf(w.c_str() , "%d#%s" , &base , nbuf)) {
      return ParseToken(new ParseTokenNUM(token , 
   }
   return ParseToken(new ParseTokenERROR(token , StringPrintF("Failed to read kestrel number from string '%s'\n" , w.c_str())));
}




const extern PARSEFUNC parser_funcs[NUM_LEXER_STATES] = {
   ParseWS,
   ParseID,
   ParseSTR,
   ParseNUM,
   ParseBLOCK,
   ParseOP,
   ParseCMT,
   0           /* No need to parse a lex error */
};

