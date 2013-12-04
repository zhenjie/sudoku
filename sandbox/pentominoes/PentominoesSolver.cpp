#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>

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
         // for each cell(i, j), we try to place pentomino on it, create a row if it fits
         // note that the pentominoes can be rotated or mirrored
         // L, N, P, F and Y can be oriented in 8 ways
         // T, and U can be oriented in 4 ways by rotation
         // V and W also can be oriented in 4 ways by rotation
         // Z can be oriented in 4 ways
         // I can be oriented in 2 ways by rotation
         // X can be oriented in only one way
         for(int p=1; p<=12; p++)
         {
            vector<vector<string> > rows;
            makeRows(i, j, p, rows);
            _rows.insert(_rows.end(), rows.begin(), rows.end());
         }

         std::sort(_rows.begin(), _rows.end());
      }
   }// for
}

vector<string> PentominoesSolver::makeRows(vector<int> &r, vector<int> &c, vector<string> row)
{
   stringstream ss;
   for(vector<int>::iterator rit = r.begin(), cit = c.begin(); rit != r.end()/* && cit != cit.end() */; ++rit, ++cit)
   {
      ss << (*rit - 1)*_column + *cit + 12;
      row.push_back(ss.str());
      ss.str(string());
   }
   
   return row;
}

void PentominoesSolver::makeRows(int i, int j, int pentomino, vector<vector<string> > &rows)
{
   vector<string> row;
   vector<int> r, c;
   switch(pentomino)
   {
   case 1: // F has 8 cases
      if(j+2 <= _column && i+2 <= _row)
      {
         row.push_back("1");

         // case 1
         r = vector<int>({i, i, i+1, i+1, i+2});
         c = vector<int>({j+1, j+2, j, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );
         
         // case 2
         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j+1, j, j+1, j+2, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j+1, j, j+1, j+2, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+2});         
         c = vector<int>({j, j+1, j+1, j+2, j+1});
         rows.push_back( makeRows(r, c, row) );
         
         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j, j, j+1, j+2, j+1});
         rows.push_back( makeRows(r, c, row) );

         // case 6
         r = vector<int>({i, i+1, i+1, i+2, i+2});
         c = vector<int>({j+1, j+1, j+2, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         // case 7
         r = vector<int>({i, i+1, i+1, i+2, i+2});
         c = vector<int>({j+1, j, j+1, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         // case 8
         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j+2, j, j+1, j+2, j+1});
         rows.push_back( makeRows(r, c, row) );
      }

      break;

   case 2: // I has two cases
      row.push_back("2");

      // case 1
      if(i+4 <= _row)
      {
         r = vector<int>({i, i+1, i+2, i+3, i+4});
         c = vector<int>({j, j, j, j, j});
         rows.push_back( makeRows(r, c, row) );
      }
      
      // case 2
      if(j + 4 <= _column)
      {
         r = vector<int>({i, i, i, i, i});
         c = vector<int>({j, j+1, j+2, j+3, j+4});
         rows.push_back( makeRows(r, c, row) );
      }
      
      break;

   case 3: // L has 8 cases
      row.push_back("3");

      if(i+1 <= _row && j+3 <= _column)
      {
         r = vector<int>({i, i, i, i, i+1});
         c = vector<int>({j, j+1, j+2, j+3, j+3});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i, i, i+1});
         c = vector<int>({j, j+1, j+2, j+3, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+1});         
         c = vector<int>({j, j, j+1, j+2, j+3});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+1});
         c = vector<int>({j+3, j, j+1, j+2, j+3});
         rows.push_back( makeRows(r, c, row) );
      }

      if(i+3 <= _row && j+1 <= _column)
      {
         r = vector<int>({i, i+1, i+2, i+3, i+3});
         c = vector<int>({j+1, j+1, j+1, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+2, i+3, i+3});
         c = vector<int>({j, j, j, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+2, i+3});
         c = vector<int>({j, j+1, j, j, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+2, i+3});
         c = vector<int>({j, j+1, j+1, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );
      }
      
      break;
   case 4: // N has 8 cases
      row.push_back("4");
      if(i+3 <= _row && j+1 <= _column)
      {
         // 4 cases here
         r = vector<int>({i, i+1, i+2, i+2, i+3});
         c = vector<int>({j, j, j, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+2, i+3});
         c = vector<int>({j, j, j+1, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+2, i+3});
         c = vector<int>({j+1, j, j+1, j, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+2, i+2, i+3});
         c = vector<int>({j+1, j+1, j, j+1, j});
         rows.push_back( makeRows(r, c, row) );
      }

      if(i+1 <= _row && j+3 <= _column)
      {
         // 4 other cases here
         r = vector<int>({i, i, i, i+1, i+1});
         c = vector<int>({j+1, j+2, j+3, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i, i+1, i+1});
         c = vector<int>({j, j+1, j+2, j+2, j+3});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+1});
         c = vector<int>({j+2, j+3, j, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+1});
         c = vector<int>({j, j+1, j+1, j+2, j+3});
         rows.push_back( makeRows(r, c, row) );
      }

      break;

   case 5: // P has 8 cases
      row.push_back("5");
      if(i+1 <= _row && j+2 <= _column)
      {
         r = vector<int>({i, i, i, i+1, i+1});
         c = vector<int>({j, j+1, j+2, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i, i+1, i+1});
         c = vector<int>({j, j+1, j+2, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+1});
         c = vector<int>({j+1, j+2, j, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+1});
         c = vector<int>({j, j+1, j, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );
      }

      if(i+2 <= _row && j+1 <= _column)
      {
         r = vector<int>({i, i, i+1, i+1, i+2});
         c = vector<int>({j, j+1, j, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+2});
         c = vector<int>({j, j+1, j, j+1, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+2, i+2});
         c = vector<int>({j, j, j+1, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+2, i+2});
         c = vector<int>({j+1, j, j+1, j, j+1});
         rows.push_back( makeRows(r, c, row) );
      }
      
      break;

   case 6: // T has 4 cases
      row.push_back("6");
      if(i+2 <= _row && j+2 <= _column)
      {
         r = vector<int>({i, i, i, i+1, i+2});
         c = vector<int>({j, j+1, j+2, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j, j, j+1, j+2, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+2, i+2, i+2});
         c = vector<int>({j+1, j+1, j, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j+2, j, j+1, j+2, j+2});
         rows.push_back( makeRows(r, c, row) );
      }

      break;

   case 7: // U has 4 cases 
      row.push_back("7");
      if(i+1 <= _row && j+2 <= _column)
      {
         r = vector<int>({i, i, i+1, i+1, i+1});
         c = vector<int>({j, j+2, j, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i, i+1, i+1});
         c = vector<int>({j, j+1, j+2, j, j+2});
         rows.push_back( makeRows(r, c, row) );
      }
      
      if(i+2 <= _row && j+1 <= _column)
      {
         r = vector<int>({i, i, i+1, i+2, i+2});
         c = vector<int>({j, j+1, j+1, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+2, i+2});
         c = vector<int>({j, j+1, j, j, j+1});
         rows.push_back( makeRows(r, c, row) );
      }

      break;

   case 8: // V has 4 cases
      row.push_back("8");
      if(i+2 <= _row && j+2 <= _column)
      {
         r = vector<int>({i, i+1, i+2, i+2, i+2});
         c = vector<int>({j, j, j, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+2, i+2, i+2});
         c = vector<int>({j+2, j+2, j, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i, i+1, i+2});
         c = vector<int>({j, j+1, j+2, j+2, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i, i+1, i+2});
         c = vector<int>({j, j+1, j+2, j, j});
         rows.push_back( makeRows(r, c, row) );
      }

      break;

   case 9: // W has 4 cases
      row.push_back("9");
      if(i+2 <= _row && j+2 <= _column)
      {
         r = vector<int>({i, i+1, i+1, i+2, i+2});
         c = vector<int>({j, j, j+1, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+2, i+2});
         c = vector<int>({j+2, j+1, j+2, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+2});
         c = vector<int>({j, j+1, j+1, j+2, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+1, i+2});
         c = vector<int>({j+1, j+2, j, j+1, j});
         rows.push_back( makeRows(r, c, row) );
      }

      break;

   case 10: // X has one case
      row.push_back("10");
      if(i+2 <= _row && j+2 <= _column)
      {
         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j+1, j, j+1, j+2, j+1});
         rows.push_back( makeRows(r, c, row) );
      }
      break;

   case 11: // Y has 8 cases
      row.push_back("11");
      if(i+1 <= _row && j+3 <= _column)
      {
         r = vector<int>({i, i, i, i, i+1});
         c = vector<int>({j, j+1, j+2, j+3, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+1});
         c = vector<int>({j+2, j, j+1, j+2, j+3});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+1});
         c = vector<int>({j+1, j, j+1, j+2, j+3});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i, i, i+1});
         c = vector<int>({j, j+1, j+2, j+3, j+2});
         rows.push_back( makeRows(r, c, row) );
      }

      if(i+3 <= _row && j+1 <= _column)
      {
         r = vector<int>({i, i+1, i+1, i+2, i+3});
         c = vector<int>({j+1, j, j+1, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );
         
         r = vector<int>({i, i+1, i+1, i+2, i+3});
         c = vector<int>({j, j, j+1, j, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+2, i+2, i+3});
         c = vector<int>({j, j, j, j+1, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+2, i+2, i+3});
         c = vector<int>({j+1, j+1, j, j+1, j+1});
         rows.push_back( makeRows(r, c, row) );
      }

      break;

   case 12: // Z has 4 cases
      row.push_back("12");
      if(i+2 <= _row && j+2 <= _column)
      {
         r = vector<int>({i, i, i+1, i+2, i+2});
         c = vector<int>({j, j+1, j+1, j+1, j+2});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j+2, j, j+1, j+2, j});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i, i+1, i+2, i+2});
         c = vector<int>({j+1, j+2, j+1, j, j+1});
         rows.push_back( makeRows(r, c, row) );

         r = vector<int>({i, i+1, i+1, i+1, i+2});
         c = vector<int>({j, j, j+1, j+2, j+2});
         rows.push_back( makeRows(r, c, row) );
      }
      break;
   default:
      break;
   };
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
      PentominoesSolution* slt = new PentominoesSolution(e, _rows, _row, _column);
      _solutions.push_back(slt);
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

void PentominoesSolver::print_rows()
{
   for(auto &e: _rows)
   {
      std::cout << "Pentomino: " << e[0] << std::endl;
      
      vector<vector<char> > m(_row, vector<char>(_column, '.'));

      for(int i=1; i<=5; i++)
      {
         int n = atoi( e[i].c_str() ) - 12;     
         m[(n-1)/_column][(n-1)%_column] = 'X';
      }

      for(auto x: m)
      {
         for(auto y: x)
         {
            std::cout << y;
         }
         std::cout << std::endl;
      }
   }
}
