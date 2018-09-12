



#ifndef Parser2_HPP
#define Parser2_HPP


#include "Lexer2.hpp"





typedef ParseToken (*PARSEFUNC)(LexToken);

ParseToken ParseWS(LexToken token);
ParseToken ParseWS(LexToken token) {
   
}
ParseToken ParseID(LexToken token);
ParseToken ParseID(LexToken token) {
   
}

ParseToken ParseNUM(LexToken token);
ParseToken ParseNUM(LexToken token) {
   
}



#endif // Parser2_HPP

