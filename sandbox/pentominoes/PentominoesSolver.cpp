#include <sstream>
#include <string>

#include "PentominoesSolver.h"
#include "DLX.h"

using std::stringstream;
using std::string;

PentominoesSolver::PentominoesSolver()
 :_row(6), _column(10)
{
   _all = false;
}

PentominoesSolver::PentominoesSolver(bool all)
{
   _all = all;
}

PentominoesSolver::PentominoesSolver(int row, int column, bool all)
 :_row(row), _column(column)
{
   // make sure:
   // _row * _column == 60
   if(row*column != 60) 
   {
      _row = 6; _column = 10;
   }

   _all = all;
}

PentominoesSolver::~PentominoesSolver()
{
   // destroy cached solutions
   for(auto pt: _solutions)
   {
      delete pt;
   }
}

void PentominoesSolver::clear()
{
   // clear base variable
   Solver::clear();
   
   // destroy cached solutions
   for(auto pt: _solutions)
   {
      delete pt;
   }
   _solutions.clear();

   // clear _elements
   _elements.clear();

   // clear _rows
   _rows.clear();
   
   // reset _row and _column
   _row = 6;
   _column = 10;
}

bool PentominoesSolver::solve()
{
   if(_solved) return _found;
   
   makeRows();
   
   makeElements();

   DLX dlx(_elements, _rows);

   _found = dlx.search(_all);
   _solved = true;

   makeSolutions(dlx.getSolutions());

   return _found;
}


/** 
 * We use Golomb's recommended names for pentominoes, i.e.,
 *   F I L P N T U V W X Y Z
 * We will make rows for labels from left to right.
 *
 * Note that there are 72 columns, the first 12 columns are used for the ONLY-ONE-Constraint, i.e., each pentomino can only be used once
 * the remaining 60 columns are used for Position-Constraint, i.e., after one pentomino has been placed, no other pentomino can be 
 * placed on positions overlapping the old one.
 *
 */
void PentominoesSolver::makeRows()
{
   for(int i=1; i<=_row; i++)
   {
      for(int j=1; j<=_column; j++)
      {
         // TODO:
      }
   }
}

void PentominoesSolver::makeElements()
{
   for(int i=1; i<=72; i++)
   {
      stringstream ss;
      ss << i;
      _elements.push_back(ss.str());
      ss.str(string());
   }
}

void PentominoesSolver::makeSolutions(vector<vector<size_t> > slt)
{
   for(vector<size_t> const &e: slt)
   {
      // SudokuSolution* sslt = new SudokuSolution(e, _rows, _row, _column);
      // _solutions.push_back(sslt);
   }
}

vector<Solution*> PentominoesSolver::getSolutions()
{ 
   return _solutions;
}

Solution* PentominoesSolver::getOneSolution()
{ 
   if(!_found)
      return nullptr;
   else
      return _solutions.front();
}

void PentominoesSolver::set_row(int row)
{
   _row = row;
}

void PentominoesSolver::set_column(int column)
{
   _column = column;
}

void PentominoesSolver::set_row_column(int row, int column)
{
   _row = row;
   _column = column;
}

void PentominoesSolver::set_find_all(bool all)
{
   _all = all;
}
