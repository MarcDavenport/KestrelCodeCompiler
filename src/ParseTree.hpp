



#ifndef ParseTree_HPP
#define ParseTree_HPP


#include <memory>
#include <list>
#include <vector>
#include <algorithm>

#include "Data.hpp"
#include "Parser2.hpp"
 









class ParseNodeBase;

class ParseNode {
   std::shared_ptr<ParseNodeBase> pbase;
   
   std::vector<ParseToken> exptokens;
   
public :
   ParseNode();
   ParseNode(ParseNodeBase* pnb);
   inline ParseNodeBase* get() {return pbase.get();}
};


ParseNode EmptyParseNode();

class ParseNodeBase {

protected :

public :
   virtual ~ParseNodeBase() {}
   
   virtual int Execute()=0;
   virtual void WriteStackCode()=0;
   
};


class KDeclaration : ParseNodeBase {
   bool is_private;
   bool is_restricted;
   ParseTokenID* pid;
   
   
   
};

class KStatement : ParseNodeBase {
   
};

class KExpression : ParseNodeBase {
   
};

class KReference : ParseNodeBase {
   
};

class KBlock {
   std::list<ParseNode> block_elements;
};


ParseNode ParseDeclaration(std::vector<ParseToken>::iterator it , std::vector<ParseToken>::iterator itend);

#if 0

<kestrel program> ::= <block> <end of file>

<block> ::= { <block element> [ ";" ] }

<block element> ::= <declaration>
                 |  <statement>

<declaration> ::= <identifier> ":" [ "private" | "restricted" ] <declarator>
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

<body> ::= <block> "end"
        |  "-"
        |  "external"

<formal parameter list> ::= "(" <formal parameters> ")"
                         |  "[" <formal parameters> "]"
                         |  "{" <formal parameters> "}"
<formal parameters> ::= <parameter> { [ "," ] <parameter> }
<parameter> ::= <identifier> ":" <parameter declarer>
<parameter declarer> ::= <type>
                      |  "var" <type>
                      |  "final" <type>

<enumeration> ::= "enum " "(" <identifier> { [ "," ] <identifier>} ")"
               |  "enum" "[" <identifier> { [ "," ] <identifier>} "]"
               |  "enum" "{" <identifier> { [ "," ] <identifier>} "}"

<subrange> ::= <expression> ".." <expression>

<pointer> ::= "@" <type>

<array> ::= "array" <type> [ "of" ] <type>
         |  "array" "of" <type>


<set> ::= "set" [ "of" ] <type>

<record> ::= "record" [ "+" <reference> ] <block> "end"



<statement> ::= <do end>
             |  <if>
             |  <case>
             |  <loop>
             |  <exception handler>
             |  <raise>
             |  <procedure call>
             |  <assignment>
             |  <return>

<do end> ::= "do"
                 <block>
             "end"

<if> ::= "if" <expression> [ "then" ]
             <block>
       [ "else"
             <block> ]
         "end"

<case> ::= "select" <expression> [ "in" ]
       { "case" <case label> { [ "," ] <case label> } ":"
             <block> }
       [ "else"
             <block> ]
         "end"

<case label> ::= <expression> [ ".." <expression> ]

<loop> ::= <while loop>
         |  <until loop>
         |  <for loop>

<while loop> ::= "while" <expression> [ "do" ]
                     <block>
                 "end"

<until loop> ::= "do"
                     <block>
                 "until" <expression>

<for loop> ::= "for" <identifier> "in" <type> [ "do" ]
                   <block>
               "end"

<exception handler> ::= "catch" <exception list> "in"
                            <block>
                      { "case" <exception list> ":"
                            <block> }
                      [ "else"
                            <block> ]
                        "end"
<exception list> ::= <reference> { [ "," ] <reference> }

<raise> ::= "raise" <reference>

<procedure call> ::= <reference> [ <expression list> ]

<assignment> ::= <reference> "=" <expression>


<return> ::= "return" <expression>

<expression> ::= <comparand> [ <comparing operator> <comparand> ]
<comparand> ::= <term> { <adding operator> <term> }
<term> ::= <factor> { <multiplying operator> <factor> }

<factor> ::= [ "-" | "~" ] <value>
<value> ::= <number>
         |  <string constant>
         |  "null"
         |  <subexpression>
         |  <reference>
<subexpression> ::= "(" <expression> ")"
                 |  "[" <expression> "]"
                 |  "{" <expression> "}"

<string constant> ::= <string>

<reference> ::= <identifier>
             |  <reference> "@"
             |  <reference> "." <identifier>
             |  <function call>
             |  <constructor call>
             |  <array reference>

<function call> ::=  <reference> [ <expression list> ]

<constructor call> ::=  <reference> [ <expression list> ]


<array reference> ::=  <reference> <expression list>

<expression list> ::= "(" <expressions> ")"
                   |  "[" <expressions> "]"
                   |  "{" <expressions> "}"

<expressions> ::= <expression> { [ "," ] <expression> }

#endif





#endif // ParseTree_HPP
