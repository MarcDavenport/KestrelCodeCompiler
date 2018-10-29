



#ifndef Rosetta_HPP
#define Rosetta_HPP

enum ERRID {
   ERR_BADSTREAM = 0,
   ERR_LEXICAL   = 1,
   ERR_PARSING   = 2,
   NUM_ERRIDS    = 3
};


#include <string>
#include <vector>



typedef const std::vector<const char*> ERRMAP;




class RosettaStone {

private :
   void Log(std::string msg);

protected :
   virtual ERRMAP& GetErrMap();

   virtual void LogErr(ERRID eid , int linenum = -1 , int colnum = -1);
public :

   virtual ~RosettaStone() {}
   
   static RosettaStone* translator;

   static void LogError(ERRID eid , int linenum = -1 , int colnum = -1);

};




#endif // Rosetta_HPP
