/**
   Data.cpp for the Kestrel compiler
   By Marc Davenport for Douglas Jones Fall 2018 Compiler Construction class
   Created : 09/18/2018
   Modified : 09/18/2018
   
   Data.cpp contains the data referenced by the compiler during lexing and parsing stages
*/

#include "Data.hpp"


const std::unordered_set<KChar> quotechars = {'\'' , '\"'};

const std::unordered_set<KChar> blockchars = {'(' , ')' , '{' , '}' , '[' , ']'};

const std::unordered_set<KChar> opchars = {
   '+','-','*','/','%','=',/// Mathematical operators
   '~','&','|','^',        /// Logical operators
   '$','<','>',':',';',    /// Assorted operators
   '.',',',                /// Stop, continue
   '@'                     /// Address op
};



/// For the parser



std::string KWStr(KEYWORD_TYPE k) {
   const static std::string kwtags[NUM_KEYWORDS + 1] = {
      // KWG_MODIFIER
      "KW_MOD_CONST",
      "KW_MOD_FINAL",
      // KWG_DECLARATION
      "KW_DEC_VAR",
      "KW_DEC_PROC",
      "KW_DEC_FUNC",
      // KWG_ACCESS
      "KW_ACC_PRIV",
      "KW_ACC_RESTRICT",
      "KW_MOD_EXTERNAL"
      // KWG_TYPE
      "KW_TYPE_TYPE",
      "KW_TYPE_ENUM",
      "KW_TYPE_ARRAY",
      "KW_TYPE_SET",
      "KW_TYPE_RECORD",
      "KW_TYPE_OF",
      // KWG_RANGE
      "KW_RANGE_IN",
      // KWG_CONTROL
      "KW_CONTROL_IF",
      "KW_CONTROL_THEN",
      "KW_CONTROL_ELSE",
      "KW_CONTROL_END",
      "KW_CONTROL_SELECT",
      "KW_CONTROL_CASE",
      // KWG_LOOP
      "KW_LOOP_WHILE",
      "KW_LOOP_DO",
      "KW_LOOP_UNTIL",
      "KW_LOOP_FOR",
      // KWG_EXCEPTION
      "KW_EXCEPT_EXCEPTION",
      "KW_EXCEPT_RAISE",
      "KW_EXCEPT_CATCH",
      "KW_EXCEPT_RETURN",
      // KWG_NULLPTR
      "KW_NULL_NULL",
      "NUM_KEYWORDS"
   };
   return kwtags[k];
}



const std::vector<KString> reserved_words = {
   KString("const"),        /// various definitions
   KString("final"),

   KString("var"),
   KString("procedure"),
   KString("function"),

   KString("private"),      /// makes a definition as private
   KString("restricted"),   /// makes a definition visible in extensions
   KString("external"),     /// mark a function as external

   KString("type"),
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

   KString("while"),        /// statement
   KString("do"),
   KString("until"),
   KString("for"),          /// statement

   KString("exception"),
   KString("raise"),        /// statement
   KString("catch"),        /// statement
   KString("return"),       /// statement

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
      KString("final")
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
      KString("restricted"),  /// makes a definition visible in extensions
      KString("external")    /// mark a function as external
   }),
   /** KWG_TYPE */
   std::unordered_set<KString>({
      KString("type"),
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





/*
enum OPNUM {
   OP_ADDRESS = 0,
   OP_FIELD   = 1,
   OP_DEFINE  = 2,
   OP_COMMA   = 3,
   OP_RANGE   = 4,
   OP_MULT    = 5,
   OP_DIV     = 6,
   OP_MOD     = 7,
   OP_PLUS    = 8,
   OP_MINUS   = 9,
   OP_NOT     = 10,
   OP_AND     = 11,
   OP_OR      = 12,
   OP_GTHAN   = 13,
   OP_LTHAN   = 14,
   OP_NEQUAL  = 15,
   OP_GEQUAL  = 16,
   OP_LEQUAL  = 17,
   OP_ASSIGN  = 18,
   OP_STOP    = 19,
   NUM_OPS    = 20
};
//*/



std::string OpStr(OPNUM op) {
   return opstrs[op];
}



const std::vector<std::string> opstrs = {
   "OP_ADDRESS",
   "OP_FIELD",
   "OP_DEFINE",
   "OP_COMMA",
   "OP_RANGE",
   "OP_MULT",
   "OP_DIV",
   "OP_MOD",
   "OP_PLUS",
   "OP_MINUS",
   "OP_NOT",
   "OP_AND",
   "OP_OR",
   "OP_GTHAN",
   "OP_LTHAN",
   "OP_NEQUAL",
   "OP_GEQUAL",
   "OP_LEQUAL",
   "OP_ASSIGN",
   "OP_STOP",
   "NUM_OPS"
};



const std::unordered_map<KString , OPNUM> operator_set = {
   std::pair<KString , OPNUM>(KString("@")  , OP_ADDRESS),  ///pointer definition and use
   std::pair<KString , OPNUM>(KString(".")  , OP_FIELD  ),  ///field selection
   std::pair<KString , OPNUM>(KString(":")  , OP_DEFINE ),  ///definition
   std::pair<KString , OPNUM>(KString(",")  , OP_COMMA  ),  ///separating expressions 

   std::pair<KString , OPNUM>(KString("..") , OP_RANGE  ),  ///subrange constructor

   std::pair<KString , OPNUM>(KString("*")  , OP_MULT   ),  ///arithmetic
   std::pair<KString , OPNUM>(KString("/")  , OP_DIV    ),  ///arithmetic
   std::pair<KString , OPNUM>(KString("%")  , OP_MOD    ),  ///arithmetic (remainder)
   std::pair<KString , OPNUM>(KString("+")  , OP_PLUS   ),  ///arithmetic
   std::pair<KString , OPNUM>(KString("-")  , OP_MINUS  ),  ///arithmetic (unary or binary)

   std::pair<KString , OPNUM>(KString("~")  , OP_NOT    ),  ///logical not or one's complement ()
   std::pair<KString , OPNUM>(KString("&")  , OP_AND    ),  ///logic
   std::pair<KString , OPNUM>(KString("|")  , OP_OR     ),  ///logic

   std::pair<KString , OPNUM>(KString(">")  , OP_GTHAN  ),  ///comparison
   std::pair<KString , OPNUM>(KString("<")  , OP_LTHAN  ),  ///comparison

   std::pair<KString , OPNUM>(KString("/=") , OP_NEQUAL ),  ///comparison
   std::pair<KString , OPNUM>(KString(">=") , OP_GEQUAL ),  ///comparison
   std::pair<KString , OPNUM>(KString("<=") , OP_LEQUAL ),  ///comparison 

   std::pair<KString , OPNUM>(KString("=")  , OP_ASSIGN ),  ///assignment and comparison

   std::pair<KString , OPNUM>(KString(";")  , OP_STOP   )   ///statement terminator/separator
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
   KString("|")   ///logic
};
const std::unordered_set<KString> operator_set_compare = {
   KString("/="), ///comparison
   KString(">"),  ///comparison
   KString(">="), ///comparison
   KString("<"),  ///comparison
   KString("<=")  ///comparison 
};

OPNUM GetOp(const KString& kstr) {
   OPNUM op = NUM_OPS;
   std::unordered_map<KString , OPNUM>::const_iterator it = operator_set.find(kstr);
   if (it != operator_set.end()) {
      op = it->second;
   }
   return op;
}

