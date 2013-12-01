/**
 * @file   Solver.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Sun Dec  1 09:47:04 2013
 * 
 * @brief  General virtual solver class for several puzzles, such as sudoku, n-queen, titling problems, etc.
 * 
 * 
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

#include "Solution.h"

using std::vector;

class Solver
{
protected:
   /// to find all solution? 
   bool all;
   
   /// any solution?
   bool found;
   
   /// is the puzzle solved?
   bool solved; 

public:
Solver():all(false), found(false), solved(false){}
   virtual ~Solver(){}

   virtual bool solve() = 0;
   virtual void clear()
   {
      all = found = solved = false;
   }
   virtual vector<Solution*> getSolutions() = 0;
   virtual Solution* getOneSolution() = 0;
};

#endif
