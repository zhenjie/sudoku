/**
 * @file   PentominoesSolver.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Tue Dec  3 04:50:52 2013
 * 
 * @brief  Pentominoes Solver.
 * 
 * 
 */

#ifndef PENTOMINOESSOLVER_H
#define PENTOMINOESSOLVER_H

#include <vector>
#include <string>

#include "Solver.h"
#include "PentominoesSolution.h"

using std::vector;
using std::string;

class PentominoesSolver : public Solver
{
private:
   int _row;
   int _column;
   vector<vector<string> > _rows;
   vector<string> _elements;
   vector<Solution*> _solutions;

   // http://en.wikipedia.org/wiki/Pentomino
   // In case we need to use any labeling scheme
   // map<int, string> _label; 
public:
   PentominoesSolver(); // default 6x10, all = false
   PentominoesSolver(bool all); // default 6x10
   PentominoesSolver(int row, int column, bool all = false);
   virtual ~PentominoesSolver();

   bool solve();
   
   void clear();
   
   void load();

   void makeRows();
   void makeElements();
   void makeSolutions(vector<vector<size_t> > slt);
   
   vector<Solution*> getSolutions();
   Solution* getOneSolution();

   void set_row(int row);
   void set_column(int column);
   void set_row_column(int row, int column);
   void set_find_all(bool all);
};
#endif
