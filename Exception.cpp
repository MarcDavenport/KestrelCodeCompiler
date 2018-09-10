
/*
 *
 *     _______       ___       ____      __       _______
 *    /\  ____\    /|   \     /  __\    /\ \     /\  ____\
 *    \ \ \___/_   ||  _ \   |  /__/____\ \ \    \ \ \___/_
 *     \ \  ____\  || |_\ \  |\ \ /\_  _\\ \ \    \ \  ____\
 *      \ \ \___/_ ||  ___ \ \ \ \\//\ \/ \ \ \____\ \ \___/_
 *       \ \______\||_|__/\_\ \ \ \_\/ |   \ \_____\\ \______\
 *        \/______/|/_/  \/_/  \_\_____/    \/_____/ \/______/
 *
 *
 *    EAGLE
 *    Edgar's Agile Gui Library and Extensions
 *
 *    Copyright 2009-2018+ by Edgar Reynaldo
 *
 *    See EagleLicense.txt for allowed uses of this library.
 *
 *    Modified by Marc Davenport aka Edgar Reynaldo for use with the Kestrel Compiler
 */



#include "Exception.hpp"
#include "Utility.hpp"



#include <cassert>
#include <iostream>


std::string EagleTraceStr(const char* exp , const char* file , int line , const char* func) {
   return StringPrintF("%s in file %s on line %d in function %s" , exp , file , line , func);
}



void LogFailedAssert(std::string info) {
   std::cerr << "Assertion failed : " << info << std::endl;
}



void LogFailedAssertAndFail(std::string info) {
   LogFailedAssert(info);
   ASSERT_EXCEPTION();
}



void Trace(std::string info) {
   std::cout << info << std::endl;
}



void EagleAssertHandler(const char* exp , const char* file , int line , const char* func) {
   LogFailedAssertAndFail(EagleTraceStr(exp , file , line , func));
}



void EpicFail() {
   int i = 1/int(0);/// debugger almost always catches this
   (void)i;
   int* p = 0;
   *p = -1;/// Why not throw in a null pointer access too?
   assert(0);
}



/// -------------------------      Exception      ----------------------------



Exception::Exception(const std::exception e) : error(e.what()) {
   std::cerr << e.what() << std::endl;
   ASSERT_EXCEPTION();
}



Exception::Exception(const std::string& e) : error(e) {
   std::cerr << e << std::endl;
   ASSERT_EXCEPTION();
}



Exception::Exception(const char* e) : error(e) {
   std::cerr << e << std::endl;
   ASSERT_EXCEPTION();
}



