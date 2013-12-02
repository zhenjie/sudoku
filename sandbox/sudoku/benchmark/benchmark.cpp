/**
 * @file   benchmark.cpp
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Mon Dec  2 09:23:38 2013
 * 
 * @brief  Simple benchmark for sudoku solver based on DLX.
 * 
 * Result:
 * zhenjie@aw-ssl:~/Workspace/sudoku/sandbox/sudoku$time ./a.out benchmark/sudoku17-ml.txt 
 *   real	9m51.056s
 *   user	8m11.359s
 *   sys	1m38.790s
 *
 * zhenjie@aw-ssl:~/Workspace/sudoku/sandbox/sudoku$time ./a.out benchmark/sudoku-20-hard.txt
 *   real	0m0.350s
 *   user	0m0.312s
 *   sys	0m0.036s
 *
 * Please compile with:
 *  g++ -std=c++11 ../SudokuSolution.cpp ../SudokuSolver.cpp ../../DLX.cpp benchmark.cpp -I.. -I../.. 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#include "SudokuSolution.h"
#include "SudokuSolver.h"

using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 2)
      cout << "./benchmark FILENAME" << endl;
   
   fstream fin;
   fin.open(argv[1], fstream::in);

   if(fin.is_open())
   {
      string line;
      while( getline(fin, line) )
      {

         if(argc == 3) cout << line.substr(0, 81) << endl;

         // each line is a sudoku
         vector<vector<int> > sudoku = vector<vector<int> > (9, vector<int>(9, 0));
         stringstream ss;
         ss.str(line.substr(0, 81));

         // read sudoku from line
         char c;         
         for(int i=0; i<81; i++)
         {
            ss >> c;
            if(c != '0' && c != '.' && c != '#')
               sudoku[i/9][i%9] = c - '0';
         }
         ss.str(string());

         // solve sudoku
         SudokuSolver solver(3, 3);
         solver.load(sudoku);
         if(argc == 3) solver.print_m();
         solver.solve();

         vector<Solution*> slts = solver.getSolutions();
         if(argc == 3)
         {
            cout << "Solutions:: " << slts.size() << endl;
            for(auto e: slts)
            {
               e->printSolution();
               cout << endl;
            }
         }         
      }//while
      fin.close();
   }
   
   return 0;
}
