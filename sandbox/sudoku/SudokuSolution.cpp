#include <iostream>
#include "SudokuSolution.h"

SudokuSolution::SudokuSolution(const vector<size_t> &slt, const vector<vector<string> > &rows, int row, int column)
{
   int base = row*column;
   _solution = vector<vector<int> >(base, vector<int>(base));

   for(size_t k: slt)
   {
      // k-1 is the index in rows
      // rows[k-1] should contains 4 elements
      int s = atoi( rows[k-1][0].c_str() ); // first element, was for Single constraint
      int r = atoi( rows[k-1][1].c_str() ); // second element, was for Row constraint

      // let's get (i, j, v) from (s, r)
      int i = ((s-1) / base) + 1; // since s = (i-1)*base + j;      
      int j = ((s-1) % base) + 1;     // since s = (i-1)*base + j;
      int v = ((r-1) % base) + 1;     // since r = (base*base) + (i-1)*base + v;
      
      _solution[i-1][j-1] = v;
   }
}

SudokuSolution::~SudokuSolution()
{
}

void SudokuSolution::printSolution()
{
   printSolution(std::cout);
}

void SudokuSolution::printSolution(std::ostream &out)
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
