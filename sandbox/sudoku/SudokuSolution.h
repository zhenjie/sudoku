/**
 * @file   SudokuSolution.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Sun Dec  1 10:30:51 2013
 * 
 * @brief  Sudoku Solution class. 
 * 
 * 
 */

#ifndef SUDOKUSOLUTION_H
#define SUDOKUSOLUTION_H

#include <ostream>
#include <vector>

#include "Solution.h"

using std::vector;

class SudokuSolution: public Solution
{
private:
   vector<vector<char> > _solution;

public:
   SudokuSolution();
   virtual ~SudokuSolution();

   void printSolution();
   void printSolution(std::ostream &out) = 0;
   void printSolutions() = 0;
   void printSolutions(std::ostream &out) = 0;
   
};


#endif
