/**
 * @file   Solution.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Sun Dec  1 10:15:09 2013
 * 
 * @brief  General virtual solution class for several puzzles, suck as sudoku, n-queen, titling problems, etc.
 * 
 * 
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include <ostream>

class Solution
{
public:
   Solution(){}
   ~Solution(){}
   
   virtual void printSolution() = 0;
   virtual void printSolution(std::ostream &out) = 0;
};

#endif
