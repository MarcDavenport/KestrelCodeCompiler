


#include "ParseTree.hpp"
#include "Exception.hpp"


ParseNode::ParseNode() : pbase(0) {}



ParseNode::ParseNode(ParseNodeBase* pnb) :
      pbase(pnb)
{}



ParseNode EmptyParseNode() {return ParseNode();}



ParseNode ParseDeclaration(TokenStream& input) {
   
   if (input.AtEnd()) {return EmptyParseNode();}
   if (!input.Peek()->IsID()) {
      EAGLE_ASSERT(input.Peek()->IsID());
      return EmptyParseNode();
   }

   /// All declarations start with an identifier followed by the define operator :
#if 0
   <declaration> ::= <identifier> ":" [ "private" | "restricted" ] <declarator>
#endif   

   bool priv = false;
   bool restrict = false;

   std::vector<ParseToken*> dectokens = input.PeekN(4);
   
   
   ParseTokenID* pid = dectokens[0]?dectokens[0]->GetIDToken():0;
   ParseTokenOP* pop = dectokens[1]?dectokens[1]->GetOpToken():0;
   ParseTokenKEYWORD* pmod = dectokens[2]?dectokens[2]->GetKeywordToken():0;

   int dec = (pmod->Group() == KWG_ACCESS)?3:2;
   if (dec == 3) {pmod = 0;}
   ParseTokenKEYWORD* pdec = dectokens[dec]?dectokens[dec]->GetKeywordToken():0;
   
   if (!pid || (!pop || (pop && pop->Op() != OP_DEFINE)) || !pdec) {
      LogError("Improperly formed declaration.\n");
   }
   
   if (pmod) {
      if (pmod->Group() == KWG_ACCESS) {
         if (pmod->WordType() == KW_ACC_PRIV) {
            priv = true;
         } else if (pmod->WordType() == KW_ACC_RESTRICT) {
            restrict = true;
         }
      }
   }
   /// Declarator
   std::vector<ParseToken> subtokens(ParseToken() , (dec == 3)?4:3);
   
   if (dectoken->Group() == KWG_DECLARATION) {
      if (dectoken->WordType() == KW_DEC_VAR) {
         /// A var, easy
         
      }
      else if (pdec->WordType() == KW_DEC_PROC) {
            
      }
      else if (pdec->WordType() == KW_DEC_FUNC) {
            
      }
   }
   else if (pdec->Group() == KWG_MODIFIER) {
      if (pdec->WordType() == KW_MOD_CONST) {
         
      }
      else if (pdec->WordType() == KW_MOD_FINAL) {
         
      }
   }
   else if (pdec->WordType() == KW_EXCEPT_EXCEPTION) {
                                       
   }
   
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

