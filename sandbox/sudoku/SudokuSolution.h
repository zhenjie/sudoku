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
#include <string>

#include "Solution.h"

using std::vector;
using std::string;

class SudokuSolution: public Solution
{
private:
   vector<vector<int> > _solution;
public:
   SudokuSolution(const vector<size_t> &slt, const vector<vector<string> > &rows, int row, int column);
   virtual ~SudokuSolution();

   void printSolution();
   void printSolution(std::ostream &out);
};


#endif
