#include "SudokuSolver.h"

SudokuSolver::SudokuSolver ()
{
}

SudokuSolver::~SudokuSolver()
{
   // destroy cached solutions
   clear();
}

bool SudokuSolver::solve()
{
   return false;
}


vector<Solution*> SudokuSolver::getSolutions()
{  
   return _solutions;
}

Solution* SudokuSolver::getOneSolution()
{
   if(!found) return nullptr;
   else return _solutions.front();
}

void SudokuSolver::clear()
{
   // clear base variable
   Solver::clear();

   // destroy cached solutions
   // ...

   for(auto pt: _solutions)
   {
      delete pt;
   }
}
