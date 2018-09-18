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


