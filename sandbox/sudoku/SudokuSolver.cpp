#include <sstream>
#include <fstream>
#include <iostream>

#include "SudokuSolver.h"
#include "SudokuSolution.h"

#include "DLX.h"

using std::stringstream;
using std::fstream;

SudokuSolver::SudokuSolver(int row, int column, bool all):_row(row), _column(column)
{
   _all = all;

   // 1) define string map for empty slot
   _stringMap["."] = 0;
   _stringMap["-"] = 0;
   _stringMap["*"] = 0;
   _stringMap["#"] = 0;
   _stringMap["0"] = 0;
   
   // 2) define string map for non-empty slot
   stringstream ss;
   for(int i=1; i<=_row*_column; i++)
   {
      ss << i;
      _stringMap[ss.str()] = i;
      ss.str(string());
   }
}

SudokuSolver::SudokuSolver(const unordered_map<string, int> &sm, int row, int column, bool all):
   _row(row), _column(column), _stringMap(sm){ _all = all; }

SudokuSolver::~SudokuSolver()
{
   // destroy cached solutions
   // destroy cached solutions
   for(auto pt: _solutions)
   {
      delete pt;
   }
}

void SudokuSolver::clear()
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
   
   // clear matrix
   _m.clear();

   // reset _row and _column to default
   _row = _column = 3;
}

vector<Solution*> SudokuSolver::getSolutions()
{  
   return _solutions;
}

Solution* SudokuSolver::getOneSolution()
{
   if(!_found) return nullptr;
   else return _solutions.front();
}

bool SudokuSolver::load(string filename)
{
   fstream fs;  
   bool status = false;
   fs.open(filename, std::fstream::in);

   if(fs.is_open())
   {
      _m = vector<vector<int> >(_row*_column, vector<int>(_row*_column, 0));

      // TODO: deal with illegal input
      string word;
      int max = _row*_column;
      for(int i=0; i<max; i++)
      {
         for(int j=0; j<max; j++)
         {
            fs >> word;
            if(fs.eof()) return false; // error
            _m[i][j] = _stringMap[ word ];   
         }
      }//for

      fs.close();
      status = true;
   }
   
   return status;
}

bool SudokuSolver::load(vector<vector<int> > &matrix)
{
   _m = matrix;
}

inline void SudokuSolver::makeRow(int i, int j, int v, vector<string> &row)
{
   int base = _row*_column;
   int s = (i-1)*base + j; // for single constraint
   int r = (base*base) + (i-1)*base + v; // for row constraint
   int c = (base*base)*2 + (j-1)*base + v; // for column constraint
   int a = (base*base)*3 + ((i-1)/_row*_row + (j-1)/_column)*base + v; // for region constraint
   
   stringstream ss;
   ss << s;
   row.push_back( string(ss.str()) );

   ss.str(string());
   ss << r;
   row.push_back( ss.str() );

   ss.str(string());
   ss << c;
   row.push_back( ss.str() );

   ss.str(string());
   ss << a;
   row.push_back( ss.str() );
}

void SudokuSolver::makeRows()
{
   // make rows 
   // we can make the names based on the (i, j, v) value
   // note that i, j, v are all in \in [1.._row*_column]
   int max = _row*_column;
   for(int i=1; i<=max; i++)
   {
      for(int j=1; j<=max; j++)
      {
         if(_m[i-1][j-1] == 0) // It's empty!
         {
            for(int v=1; v<=max; v++)
            {
               vector<string> vs;
               makeRow(i, j, v, vs);
               _rows.push_back(vs);
            }
         }//if
         else
         {
            // The value is known, simply put one row in 
            vector<string> vs;
            makeRow(i, j, _m[i-1][j-1], vs);
            _rows.push_back(vs);
         }
      }
   }//for
}

void SudokuSolver::makeElements()
{
   // make _elements based on _rows
   // wow! we got a magic constant 4!

   // one way:
   // unordered_map<string, bool> map;
   // for(int i=0; i<4; i++)
   // {
   //    for(auto const &e: _rows)
   //    {
   //       if(map.find(e[i]) == map.end())
   //       {
   //          _elements.push_back(e[i]);
   //          map[e[i]] = true;
   //       }
   //    }
   // }//for

   // another way:
   // We have (_row*_column)^2*4 columns
   stringstream ss;
   for(int i=1; i<=(_row*_column)*(_row*_column)*4; i++)
   {
      ss << i;
      _elements.push_back(ss.str());
      ss.str(string());
   }
}

bool SudokuSolver::solve()
{
   if(_solved) return _found;

   // 1) convert _m to exact cover problem, i.e., a set of elements(columns' name) and a set of rows
   //    (_row*_column)^2*4 columns and (_row*_column)^3 rows
   // as for the initial setup, they will not be the rows
   makeRows();

   // 2) make elements
   makeElements();

   DLX dlx(_elements, _rows);

   _found = dlx.search(_all);
   _solved = true;
   
   makeSolutions(dlx.getSolutions());

   return _found;
}

void SudokuSolver::makeSolutions(vector<vector<size_t> > slt)
{
   for(vector<size_t> const &e: slt)
   {
      SudokuSolution* sslt = new SudokuSolution(e, _rows, _row, _column);
      _solutions.push_back(sslt);
   }
}

void SudokuSolver::set_row(int row)
{
   _row = row;
}

void SudokuSolver::set_column(int column)
{
   _column = column;
}

void SudokuSolver::set_row_column(int row, int column)
{
   _row = row;
   _column = column;
}

void SudokuSolver::set_find_all(bool all)
{
   _all = all;
}

void SudokuSolver::set_stringMap(const unordered_map<string, int> &sm)
{
   _stringMap = sm;
}

void SudokuSolver::print_m()
{
   for(auto const &e: _m)
   {
      for(auto const &x: e)
      {
         std::cout << x << " ";
      }
      std::cout << std::endl;
   }
}

void SudokuSolver::print_stringMap()
{
   for(auto const &e: _stringMap)
      std::cout << e.first << ":" << e.second << std::endl;
}

void SudokuSolver::print_elements()
{
   for(auto const &e: _elements)
   {
      std::cout << e << " ";
   }
   std::cout << std::endl;
}

void SudokuSolver::print_rows()
{
   for(auto const &e: _rows)
   {
      for(auto const &x: e)
      {
         std::cout << x << " ";
      }
      std::cout << std::endl;
   }
}
