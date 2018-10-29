



#ifndef TokenStream_HPP
#define TokenStream_HPP



#include "Parser2.hpp"
#include <vector>



class TokenStream {
   std::vector<ParseToken> ptokens;
   unsigned int iter;
   
public :
   TokenStream() : ptokens() , iter(0) {}
   
   void ResetStream();
   bool AtEnd();
   void PushBack(const ParseToken& ptoken);
   
   ParseToken*              Peek ();
   std::vector<ParseToken*> PeekN(unsigned int N);
   
   bool         Extract  (ParseToken* pstore);
   bool         ExtractTo(std::vector<ParseToken>& tokvec);
   unsigned int ExtractN (unsigned int N , ParseToken* pstore);
   unsigned int ExtractNTo(unsigned int N , std::vector<ParseToken>& tokvec);
};



#endif // TokenStream_HPP





