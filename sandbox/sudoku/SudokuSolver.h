/**
 * @file   SudokuSolver.h
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Sun Dec  1 09:53:41 2013
 * 
 * @brief  Sudoku solver.
 * 
 * 
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Solver.h"
#include "Solution.h"

using std::vector;
using std::unordered_map;
using std::string;

class SudokuSolver : public Solver
{
private:
   /// character map, map from input character to internal datastructure, int
   unordered_map<string, int> _stringMap;

   /// row, default 3
   int _row;

   /// column, default, 3
   int _column;

   /// rows with name
   vector<vector<string> > _rows;
   
   /// elements, columns' name
   vector<string> _elements;

   /// solutions' container 
   vector<Solution*> _solutions;
   
   /// initial sudoku matrix, not exact cover matrix
   /// we use *int* for each cell, 0 means empty
   vector< vector<int> > _m;
   
public:
   explicit SudokuSolver(int row=3, int column=3, bool all = false);
   SudokuSolver(const unordered_map<string, int> &sm, int row=3, int column=3, bool all = false);

   virtual ~SudokuSolver();
   
   /** 
    * Load sudoku from file
    * 
    * @param filename File name.
    * 
    * @return true if load successfully; false otherwise.
    */
   bool load(string filename);
   bool load(vector<vector<int> > &matrix);

   bool solve();
   
   void clear();

   vector<Solution*> getSolutions();
   Solution* getOneSolution();

   void set_row(int row);
   void set_column(int column);
   void set_row_column(int row, int column);
   void set_find_all(bool all);
   void set_stringMap(const unordered_map<string, int> &sm);
private:
   void makeRow(int i, int j, int k, vector<string> &row);
   void makeSolutions(vector<vector<size_t> > slt);
   void makeRows();
   void makeElements();

public:
   void print_m();
   void print_stringMap();
   void print_elements();
   void print_rows();
};

#endif
