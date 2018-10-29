



#include "TokenStream.hpp"



void TokenStream::ResetStream() {
   iter = 0;
}



bool TokenStream::AtEnd() {
   return iter >= ptokens.size();
}



void TokenStream::PushBack(const ParseToken& ptoken) {
   ptokens.push_back(ptoken);
}



ParseToken* TokenStream::Peek() {
   if (iter >= ptokens.size()) {return 0;}
   return &ptoken[iter];
}



std::vector<ParseToken*> PeekN(unsigned int N) {
   std::vector<ParseToken*> tokens((ParseToken*)0 , N);
   for (unsigned int it = iter ; (it < iter + N) && (it < ptokens.size()) ; ++it) {
      tokens[it - iter] = &(ptokens[it]);
   }
   return tokens;
}



bool TokenStream::Extract(ParseToken* pstore) {
   EAGLE_ASSERT(pstore);
   ParseToken* pt = Peek();
   if (pt) {*pstore = ptokens[iter++];}
   return (bool)pt;
}



bool TokenStream::ExtractTo(std::vector<ParseToken>& tokvec) {
   tokvec.resize(tokvec.size() + 1);
   return Extract(&tokvec.back());
}



unsigned int TokenStream::ExtractN(unsigned int N , ParseToken* pstore) {
   if (N == 0) {return false;}
   EAGLE_ASSERT(pstore);
   
   std::vector<ParseToken*> tokens = PeekN(N);

   /// tokens will be padded with zeros if nothing could be found, trim here
   while (N && !tokens.back()) {
      tokens.pop_back();
      --N;
   }
   
   for (unsigned int i = 0 ; i < N ; ++i) {
      *pstore++ = tokens[i];
      if (!tokens[i]) {
         success = false;
      }
   }
   return N;
}



unsigned int TokenStream::ExtractNTo(unsigned int N , std::vector<ParseToken>& tokvec) {
   unsigned int end = tokvec.size();
   tokvec.resize(tokvec.size() + N);
   return ExtractN(N , &tokvec[end]);
}

