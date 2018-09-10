/**
   Error.hpp by Marc Davenport for Compiler Construction
   Created : 09/07/2018
   Last update : 09/07/2018
   
   This file contains the interface and implementation of the Exception class,
   a simple class for logging run time exceptions.
*/

#ifndef Error_HPP
#define Error_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
   
   std::string err;
   
public :
   Exception(std::string error) :
         std::exception(),
         err(error)
   {}
   
   const char* what() const noexcept {return err.c_str();}
};

#endif // Error_HPP

