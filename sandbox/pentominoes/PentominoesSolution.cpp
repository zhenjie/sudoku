#include <iostream>

#include "PentominoesSolution.h"

PentominoesSolution::PentominoesSolution(){}

PentominoesSolution::~PentominoesSolution(){}

void PentominoesSolution::printSolution()
{
   printSolution(std::cout);
}

void PentominoesSolution::printSolution(std::ostream &out)
{
   for(auto e: _solution)
   {
      for(auto x: e)
      {
         out << x << "\t";
      }
      out << std::endl;
   }
}

