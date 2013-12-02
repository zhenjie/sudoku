#include <unordered_map>
#include <iostream>
#include <limits>
#include "DLX.h"

using std::unordered_map;
using std::numeric_limits;
using std::ofstream;

DLX::DLX(){}

DLX::DLX(vector<string> &elements, vector<vector<string> > &rows):_rows(rows)
{
   size_t sz = elements.size();
   size_t rsz = rows.size();

   _matrix = vector<vector<Column> > (rsz+1, vector<Column>(sz+1));

   Column root;
   root.left = sz;
   root.right = 1;
   
   unordered_map<string, size_t> name_hash;
   _matrix[0][0] = root;
   for(size_t i=1; i<=sz; i++)
   {
      Column column;
      column.left = i-1;
      column.right = (i+1)%(sz+1); 
      column.up = 0;
      column.down = 0;
      
      column.size = 0;
      column.name = elements[i-1];
      _matrix[0][i] = column;
      name_hash[elements[i-1]] = i;
   }
   
   for(int i=1; i<=rsz; i++)
   {
      Column last;
      // construct vector<Data> row for each row: rows[i-1]
      for(string const &e: rows[i-1])
      {
         // r: i, c: name_hash[ e ]
         size_t r = i;
         size_t c = name_hash[e];
         Column obj;

         // 1) set up and down
         obj.up = _matrix[0][c].up;
         obj.down = 0;
            
         _matrix[ _matrix[0][c].up ][c].down = r;
         _matrix[0][c].up = r;
         _matrix[0][c].size++;

         // 2) set left and right
         if(last.left != 0)
         {
            obj.left = _matrix[r][ last.right ].left;
            obj.right = last.right;
            
            _matrix[r][ last.right ].left = c;
            _matrix[r][ obj.left ].right = c;
         }
         else
         {
            // last is not set, which means obj is the first
            obj.left = c;
            obj.right = c;
         }

         last = obj;
         _matrix[r][c] = obj;
      }
   }// for
}

bool DLX::search(bool all)
{
   // clear
   _solutions.clear();

   vector<size_t> slt;
   search(slt, all);

   return !_solutions.empty();
}

void DLX::search(vector<size_t> &slt, bool all = false)
{
   if(!_solutions.empty() && !all) return;

   // empty _matrix 
   if(_matrix[0][0].right == 0) 
   {
      _solutions.push_back(slt);
      return;
   }
   
   // 1) choose a column object c
   size_t c = getNextColumn();

   // 2) cover column c
   coverColumn(c);

   // 3) do the recursive job
   size_t r = _matrix[0][c].down;
   while(r != 0)
   {
      slt.push_back(r);

      size_t j = _matrix[r][c].right;
      while(j != c)
      {
         coverColumn(j);
         j = _matrix[r][j].right;
      }
      
      search(slt, all);

      r = slt.back();
      slt.pop_back();

      j = _matrix[r][c].left;
      while(j != c)
      {
         uncoverColumn(j);
         j = _matrix[r][j].left;
      }

      r = _matrix[r][c].down;
   }
   // 4) uncover column c and return
   uncoverColumn(c);
}

size_t DLX::getNextColumn()
{
   size_t c = 0;
   size_t sz = numeric_limits<int>::max();
   size_t i = _matrix[0][0].right;
   while(i != 0)
   {
      if(_matrix[0][i].size < sz)
      {
         sz = _matrix[0][i].size;
         c = i;
      }
      i = _matrix[0][i].right;
   }

   return c;
}

void DLX::coverColumn(size_t c)
{
   // 1) cover head list
   size_t r = _matrix[0][c].right;
   _matrix[0][r].left = _matrix[0][c].left;

   size_t l = _matrix[0][c].left;
   _matrix[0][l].right = _matrix[0][c].right;
   
   // 2) cover each row in column c
   size_t i = _matrix[0][c].down;
   while(i != 0)
   {
      // cover row i
      size_t j = _matrix[i][c].right;
      while(j != c)
      {
         size_t d = _matrix[i][j].down;
         _matrix[d][j].up = _matrix[i][j].up;

         size_t u = _matrix[i][j].up;
         _matrix[u][j].down = _matrix[i][j].down;
         
         --_matrix[0][j].size;
         j = _matrix[i][j].right;
         
      }
      i = _matrix[i][c].down;
   }// while
}

void DLX::uncoverColumn(size_t c)
{
   // 1) uncover each row in column c
   size_t i = _matrix[0][c].up;
   while(i != 0)
   {
      // uncover row i
      size_t j = _matrix[i][c].left;
      while(j != c)
      {
         size_t d = _matrix[i][j].down;
         _matrix[d][j].up = i;
         
         size_t u = _matrix[i][j].up;
         _matrix[u][j].down = i;

         ++_matrix[0][j].size;
         j = _matrix[i][j].left;
      }
      i = _matrix[i][c].up;
   }// while

   // 2) uncover head list
   size_t r = _matrix[0][c].right;
   _matrix[0][r].left = c;
   
   size_t l = _matrix[0][c].left;
   _matrix[0][l].right = c;
}

vector<vector<size_t> > DLX::getSolutions()
{
   return _solutions;
}

void DLX::printMatrix()
{
   for(auto const &e: _matrix)
   {
      for(auto const &x: e)
      {
         std::cout << x.name;
         std::cout << "(" << x.left << ", " << x.right << ", " << x.up
                   << ", " << x.down << ", " << x.size << ") ";
      }
      std::cout << std::endl;
   }
}

void DLX::printUncoveredMatrixHeader()
{
   Column x = _matrix[0][0];
   std::cout << "Root: (" << x.left << ", " << x.right << ", " << x.up
             << ", " << x.down << ", " << x.size << ") " << std::endl;
   
   size_t r = x.right;
   while(r != 0)
   {
      Column x = _matrix[0][r];
      std::cout << "(" << x.left << ", " << x.right << ", " << x.up
                << ", " << x.down << ", " << x.size << ") ";
      
      r = x.right;
   }
   std::cout << std::endl;
}

void DLX::printSolutions(ostream &out)
{
   for(auto const &e: _solutions)
   {
      for(auto const &x: e)
         out << x << " ";
      out << std::endl;
   }
}

void DLX::printSolutionsRows(ostream &out)
{
   for(auto const &e: _solutions)
   {
      for(auto const &x: e)
      {
         for(auto const &st: _rows[x-1])
            out << st << " ";
         out << std::endl;
      }
   }//for
}
