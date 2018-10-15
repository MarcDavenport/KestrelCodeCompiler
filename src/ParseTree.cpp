


#include "ParseTree.hpp"
#include "Exception.hpp"


ParseNode::ParseNode() : pbase(0) {}



ParseNode::ParseNode(ParseNodeBase* pnb) :
      pbase(pnb)
{}



ParseNode EmptyParseNode() {return ParseNode();}



ParseNode ParseDeclaration(std::vector<ParseToken>::iterator it , std::vector<ParseToken>::iterator itend) {
   
   bool priv = false;
   bool restrict = false;

   ParseTokenID* pid = 0;
   ParseTokenKEYWORD* dectoken = 0;
   ParseTokenOP* psop = 0;

   /// All declarations start with an identifier followed by the define operator :
#if 0
   <declaration> ::= <identifier> ":" [ "private" | "restricted" ] <declarator>
#endif   
   std::vector<ParseToken>::iterator it2 = it;

   if (it == itend) {return EmptyParseNode();}

   pid = dynamic_cast<ParseTokenID*>(it->get());/// save for later

   ++it2;
   if (it->ParserType() != PARSE_IDENTIFIER) {
       /// All declarations start with an identifier, return empty node
       return EmptyParseNode();
   }
   if (it2 == itend) {
#warning TODO : ERROR_MISSING_DECLARATION_OPERATOR undefined, also, this is clumsy
///      error = "MISSING : in declaration\n";
///      LogError(ERROR_MISSING_DECLARATION_OPERATOR , it2->LexToken());
      goto error;
   }
   if (it2->ParserType() == PARSE_OPERATOR) {
      psop = dynamic_cast<ParseTokenOP*>(it2->get());
   }
   if (!psop) {
#warning TODO :       LogErrorExpected(RS_OPERATOR , it2->LexerToken());
///      LogErrorExpected(RS_OPERATOR , it2->LexerToken());
      goto error;
   }
   if (psop->Op() != OP_DEFINE) {
      #warning ERROR_MISSING_DEFINE_OPERATOR error code unimplemented
///      LogErrorExpected(ERROR_MISSING_DEFINE_OPERATOR , it2->LexerToken());
      goto error;
   }

   /// Optional private or restricted keyword, followed by declarator  
   ++it2;/// Move to optional keyword
   if (it2 == itend) {
      #warning ERROR_EXPRECTED_DECLARATOR error code unimplemented
///      LogError(ERROR_EXPECTED_DECLARATOR , it2->LexerToken());
      goto error;
   }

   if (it2->ParserType() == PARSE_KEYWORD) {
      ParseTokenKEYWORD* ptkeyword = dynamic_cast<ParseTokenKEYWORD*>(it2->get());
      if (ptkeyword->Group() == KWG_ACCESS && ptkeyword->WordType() == KW_ACC_PRIV) {
         priv = true;
      } else if (ptkeyword->Group() == KWG_ACCESS && ptkeyword->WordType() == KW_ACC_RESTRICT) {
         restrict = true;
      }
      else {
#warning TODO :          LogError(ERROR_ILLEGAL_KEYWORD_IN_DECLARATION , it2->LexToken());
///         LogError(ERROR_ILLEGAL_KEYWORD_IN_DECLARATION , it2->LexToken());
         goto error;
      }
      ++it2;
      if (it2 == itend) {
#warning TODO :          LogError(ERROR_EXPRECTED_DECLARATOR , it2->LexerToken());
///         LogError(ERROR_EXPRECTED_DECLARATOR , it2->LexerToken());
         goto error;
      }
   }
   
   /// Declarator
   
   if (it2->ParserType() != PARSE_KEYWORD) {
#warning TODO :       LogErrorExpected(ERROR_MISSING_KEYWORD , it2->LexerToken());
///      LogErrorExpected(ERROR_MISSING_KEYWORD , it2->LexerToken());
      goto error;
   }

   dectoken = dynamic_cast<ParseTokenKEYWORD*>(it2->get());
   
   EAGLE_ASSERT(dectoken);
   
///   if (kwtoken->Group() !=
   
   
///   switch
   
   
   
   
///   return KDeclaration(...);
   
   error:
   return EmptyParseNode();
}
#if 0

<declarator> ::= <constant declarator>
              |  <type declarator>
              |  <exception declarator>
              |  <variable declarator>
              |  <procedure declarator>
              |  <function declarator>

<constant declarator> ::= "const" <expression>
                       |  "final" <expression>


<type declarator> ::= "type" <type>
                   |  "type" "-"

<exception declarator> ::= "exception"

<variable declarator> ::= "var" <type>

<procedure declarator> ::= "procedure"
                           [ <formal parameter list> ]
                           <body>
<function declarator> ::=  "function" <type>
                           [ <formal parameter list> ]
                           <body>

#endif

