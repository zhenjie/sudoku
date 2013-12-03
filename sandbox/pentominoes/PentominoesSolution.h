/**
 * @file   PentominoesSolution.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Tue Dec  3 04:57:02 2013
 * 
 * @brief  Solution.
 * 
 * 
 */
#ifndef PENTOMINOESSOLUTION_H
#define PENTOMINOESSOLUTION_H

#include <ostream>
#include <vector>
#include <string>

#include "Solution.h"

using std::vector;
using std::string;

class PentominoesSolution: public Solution
{
private:
   vector<vector<int> > _solution;
public:
   PentominoesSolution();
   virtual ~PentominoesSolution();

   void printSolution();
   void printSolution(std::ostream &out);
};


#endif
