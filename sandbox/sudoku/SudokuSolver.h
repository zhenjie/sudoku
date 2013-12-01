/**
 * @file   SudokuSolver.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Sun Dec  1 09:53:41 2013
 * 
 * @brief  Sudoku solver.
 * 
 * 
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

#include "Solver.h"
#include "Solution.h"

using std::vector;

class SudokuSolver : public Solver
{
private:
   vector<Solution*> _solutions;

public:
   SudokuSolver();
   virtual ~SudokuSolver();

   bool solve();
   
   void clear();

   vector<Solution*> getSolutions();
   Solution* getOneSolution();
};

#endif
