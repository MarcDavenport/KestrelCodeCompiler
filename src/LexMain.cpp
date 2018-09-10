



#include <fstream>
#include <string>

#include "Lexer2.hpp"
#include "Exception.hpp"

/// https://svn.divms.uiowa.edu/repos/cs4980
/// <img src="https://media.giphy.com/media/tYtQwLrP40HSw/giphy.gif" />


int main(int argc , char** argv) {
   
   signal(SIGABRT, signal_handler);
   // _set_abort_behavior(0, _WRITE_ABORT_MSG|_CALL_REPORTFAULT);

   std::set_terminate(EpicFail);
   std::set_unexpected(EpicFail);

   Lexer2 lex;
   
///   EAGLE_ASSERT(lex.LexerState(-1) == LEX_ERROR);
   
///   lex.DumpStateTable(std::cout);

   for (int i = 1 ; i < argc ; ++i) {
      std::ifstream fin(argv[i]);
      if (fin.good()) {
         lex.Lexify(fin);
         fin.close();
         std::string opstr = std::string(argv[i]) + ".klx.txt";
         std::ofstream fout(opstr.c_str());
         if (fout.good()) {
            lex.WriteTags(fout);
            fout.close();
         }
      }
   }
   
   return 0;
}

