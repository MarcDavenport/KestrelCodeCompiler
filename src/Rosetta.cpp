



#include "Rosetta.hpp"
#include "Utility.hpp"

#warning TODO : REMOVE dependence on cout
#include <iostream>



const std::vector<const char*> errmap_english = {
   "Bad stream",    /// ERR_BADSTREAM
   "Lexical error", /// ERR_LEXICAL
   "Parsing error", /// ERR_PARSING
   "Unknown error"  /// NUM_ERRIDS
};



ERRMAP& RosettaStone::GetErrMap() {return errmap_english;}



void RosettaStone::Log(std::string msg) {
   std::cout << msg << std::endl;
}



void RosettaStone::LogErr(ERRID eid , int linenum , int colnum) {
   ERRMAP& errmap = translator->GetErrMap();
   std::string err = "ERROR : ";
   err += errmap[eid];
   if (linenum != -1 && colnum != -1) {
      std::string err = StringPrintF("ERROR : %s on line %d on column %d." , errmap[eid] , linenum , colnum);
   }
}



RosettaStone rs_english;



RosettaStone* RosettaStone::translator = &rs_english;



void RosettaStone::LogError(ERRID eid , int linenum , int colnum) {
   translator->LogErr(eid , linenum , colnum);
}
