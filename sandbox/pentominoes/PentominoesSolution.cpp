#include <iostream>

#include "PentominoesSolution.h"

PentominoesSolution::PentominoesSolution(const vector<size_t> &slt, const vector<vector<string> > &rows, int row, int column)
{
   _solution = vector<vector<int> >(row, vector<int>(column, 0));
   for(size_t i: slt)
   {
      // rows[i-1][0] is the name(1..12) of pentomino
      // rows[i-1][1..5] is the position of this pentomino
      for(int j=1; j<=5; j++)
      {
         int pentomino = atoi( rows[i-1][0].c_str() );
         int n = atoi( rows[i-1][j].c_str() ) - 12;
         _solution[ (n-1)/column ][ (n-1)%column ] = pentomino;
      }
   }   
}

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

