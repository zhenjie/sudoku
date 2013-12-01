#include <unordered_map>
#include <iostream>
#include <limits>
#include "dlx.h"

using std::unordered_map;
using std::numeric_limits;

DLX::DLX(){}

DLX::DLX(vector<string> &elements, vector<vector<string> > &rows)
{
   size_t sz = elements.size();
   size_t rsz = rows.size();

   matrix = vector<vector<Column> > (rsz+1, vector<Column>(sz+1));

   Column root;
   root.left = sz;
   root.right = 1;
   
   unordered_map<string, size_t> name_hash;
   matrix[0][0] = root;
   for(size_t i=1; i<=sz; i++)
   {
      Column column;
      column.left = i-1;
      column.right = (i+1)%(sz+1); 
      column.up = 0;
      column.down = 0;
      
      column.size = 0;
      column.name = elements[i-1];
      matrix[0][i] = column;
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
         obj.up = matrix[0][c].up;
         obj.down = 0;
            
         matrix[ matrix[0][c].up ][c].down = r;
         matrix[0][c].up = r;
         matrix[0][c].size++;

         // 2) set left and right
         if(last.left != 0)
         {
            obj.left = matrix[r][ last.right ].left;
            obj.right = last.right;
            
            matrix[r][ last.right ].left = c;
            matrix[r][ obj.left ].right = c;
         }
         else
         {
            // last is not set, which means obj is the first
            obj.left = c;
            obj.right = c;
         }

         last = obj;
         matrix[r][c] = obj;
      }
   }// for
}

void DLX::search(bool all = false)
{
   // clear
   solutions.clear();

   vector<size_t> slt;
   search(slt, all);

   printSolutions();
}

void DLX::search(vector<size_t> &slt, bool all = false)
{
   if(!solutions.empty() && !all) return;

   // empty matrix 
   if(matrix[0][0].right == 0) 
   {
      solutions.push_back(slt);
      return;
   }
   
   // 1) choose a column object c
   size_t c = getNextColumn();

   // 2) cover column c
   coverColumn(c);

   // 3) do the recursive job
   size_t r = matrix[0][c].down;
   while(r != 0)
   {
      slt.push_back(r);

      size_t j = matrix[r][c].right;
      while(j != c)
      {
         coverColumn(j);
         j = matrix[r][j].right;
      }
      
      search(slt, all);

      r = slt.back();
      slt.pop_back();

      j = matrix[r][c].left;
      while(j != c)
      {
         uncoverColumn(j);
         j = matrix[r][j].left;
      }

      r = matrix[r][c].down;
   }
   // 4) uncover column c and return
   uncoverColumn(c);
}

size_t DLX::getNextColumn()
{
   size_t c = 0;
   size_t sz = numeric_limits<int>::max();
   size_t i = matrix[0][0].right;
   while(i != 0)
   {
      if(matrix[0][i].size < sz)
      {
         sz = matrix[0][i].size;
         c = i;
      }
      i = matrix[0][i].right;
   }

   return c;
}

void DLX::coverColumn(size_t c)
{
   // 1) cover head list
   size_t r = matrix[0][c].right;
   matrix[0][r].left = matrix[0][c].left;

   size_t l = matrix[0][c].left;
   matrix[0][l].right = matrix[0][c].right;
   
   // 2) cover each row in column c
   size_t i = matrix[0][c].down;
   while(i != 0)
   {
      // cover row i
      size_t j = matrix[i][c].right;
      while(j != c)
      {
         size_t d = matrix[i][j].down;
         matrix[d][j].up = matrix[i][j].up;

         size_t u = matrix[i][j].up;
         matrix[u][j].down = matrix[i][j].down;
         
         --matrix[0][j].size;
         j = matrix[i][j].right;
         
      }
      i = matrix[i][c].down;
   }// while
}

void DLX::uncoverColumn(size_t c)
{
   // 1) uncover each row in column c
   size_t i = matrix[0][c].up;
   while(i != 0)
   {
      // uncover row i
      size_t j = matrix[i][c].left;
      while(j != c)
      {
         size_t d = matrix[i][j].down;
         matrix[d][j].up = i;
         
         size_t u = matrix[i][j].up;
         matrix[u][j].down = i;

         ++matrix[0][j].size;
         j = matrix[i][j].left;
      }
      i = matrix[i][c].up;
   }// while

   // 2) uncover head list
   size_t r = matrix[0][c].right;
   matrix[0][r].left = c;
   
   size_t l = matrix[0][c].left;
   matrix[0][l].right = c;
}

void DLX::printMatrix()
{
   for(auto const &e: matrix)
   {
      for(auto const &x: e)
      {
         std::cout << x.name;
         std::cout << "(" << x.left << ", " << x.right << ", " << x.up
                   << ", " << x.down << ", " << ", " << x.size << ") ";
      }
      std::cout << std::endl;
   }
}

void DLX::printUncoveredMatrixHeader()
{
   Column x = matrix[0][0];
   std::cout << "Root: (" << x.left << ", " << x.right << ", " << x.up
             << ", " << x.down << ", " << ", " << x.size << ") " << std::endl;
   
   size_t r = x.right;
   while(r != 0)
   {
      Column x = matrix[0][r];
      std::cout << "(" << x.left << ", " << x.right << ", " << x.up
                << ", " << x.down << ", " << ", " << x.size << ") ";
      
      r = x.right;
   }
   std::cout << std::endl;
}

void DLX::printSolutions()
{
   for(auto const &e: solutions)
   {
      for(size_t const &x: e)
         std::cout << x << " ";
      std::cout << std::endl;
   }
}
