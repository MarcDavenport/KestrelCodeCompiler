



#include <fstream>
#include <string>

#include "Lexer2.hpp"
#include "Exception.hpp"
#include "Parser2.hpp"


/// https://svn.divms.uiowa.edu/repos/cs4980
/// <img src="https://media.giphy.com/media/tYtQwLrP40HSw/giphy.gif" />


int main(int argc , char** argv) {
   
   signal(SIGABRT, signal_handler);

   std::set_terminate(EpicFail);
   std::set_unexpected(EpicFail);

   

   
   for (int i = 1 ; i < argc ; ++i) {
      std::ifstream fin(argv[i]);

      if (!fin.good()) {
         std::cerr << "Could not open input file (" << argv[i] << ") for reading." << std::endl;
         continue;
      }

      Lexer2 lex;
      lex.Lexify(fin);
      fin.close();

      std::string opfile = std::string(argv[i]) + ".kcc.txt";
      std::ofstream fout(opfile.c_str());
      
      std::ostream* output = fout.good()?&fout:&std::cout;

      *output << "SANITY PHASE {" << std::endl;
      lex.WriteWords(*output);
      *output << "}\n" << std::endl;
      
      *output << "LEXING PHASE {" << std::endl;
      lex.WriteTags(*output);
      *output << "}\n" << std::endl;
      
      Parser parser;
      parser.Parse(lex.Tokens());

      *output << "PARSING PHASE {" << std::endl;
      parser.WriteTags(*output);
      *output << "}\n" << std::endl;
      
      fout.close();
   }

   return 0;
}

