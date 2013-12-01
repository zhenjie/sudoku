/**
 * @file   dlx.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Sat Nov 30 06:57:03 2013
 * 
 * @brief  dlx
 * 
 * 
 */

#ifndef DLX_H
#define DLX_H

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Data
{
   size_t left = 0;
   size_t right = 0;
   size_t up = 0;
   size_t down = 0;
};

struct Column : public Data
{
   size_t size = 0;
   string name;
};

class DLX
{
private:
   /// matrix[0][0] is the root
   /// 
   vector<vector<Column> > matrix;
   vector<vector<size_t> > solutions;
public:
   DLX();

   /** 
    * Construct matrix from elements and rows.
    * 
    * @param rows 
    */
   DLX(vector<string> &elements, vector<vector<string> > &rows);

   /** 
    * Do the recursive search
    * 
    */
   void search(vector<size_t> &slt, bool all);
   void search(bool all);

   /** 
    * Get next column, can apply different strategies
    * 
    * @return The column index
    */
   size_t getNextColumn();

   /** 
    * Cover column c.
    * 
    * @param c column c.
    */
   void coverColumn(size_t c);

   /** 
    * Uncover column c.
    * 
    * @param c column c.
    */
   void uncoverColumn(size_t c);
      
   /** 
    * Print the matrix
    * 
    */
   void printMatrix();

   void printUncoveredMatrixHeader();

   void printSolutions();
};


#endif
