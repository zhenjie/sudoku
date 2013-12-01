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
#include <ostream>

using std::string;
using std::vector;
using std::ostream;

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
   vector<vector<Column> > _matrix;
   vector<vector<size_t> > _solutions;
   vector<vector<string> > _rows;
public:
   DLX();

   /** 
    * Construct matrix from elements and rows.
    * 
    * @param rows 
    */
   DLX(vector<string> &elements, vector<vector<string> > &rows);

   void search(bool all);

   vector<vector<size_t> > getSolutions();

private:
   /** 
    * Do the recursive search
    * 
    */
   void search(vector<size_t> &slt, bool all);

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

private:
   /** 
    * Print the matrix, for debugging.
    * 
    */
   void printMatrix();
   void printUncoveredMatrixHeader();
   void printSolutions(ostream &out);
   void printSolutionsRows(ostream &out);
};


#endif
