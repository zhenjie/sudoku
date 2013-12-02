/**
 * @file   simplesolver-benchmark.cpp
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Mon Dec  2 09:57:28 2013
 * 
 * @brief  Sudoku solver using naive backtrack, no optimiaztion. 
 * 
 * The result is unacceptable.
 * zhenjie@aw-ssl:~/Workspace/sudoku/sandbox/sudoku/benchmark$time ./a.out sudoku-20-hard.txt
 *   real	2m29.532s
 *   user	2m29.425s
 *   sys	0m0.004s
 * It's roughly 4285 times slower than DLX implementation without optimization.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SimpleSolver.cpp"

using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 2)
      cout << "./simplesolver-benchmark FILENAME" << endl;
   
   fstream fin;
   fin.open(argv[1], fstream::in);

   if(fin.is_open())
   {
      string line;
      while( getline(fin, line) )
      {

         if(argc == 3) cout << line.substr(0, 81) << endl;

         // each line is a sudoku
         vector<vector<char> > sudoku = vector<vector<char> > (9, vector<char>(9, '.'));
         stringstream ss;
         ss.str(line.substr(0, 81));

         // read sudoku from line
         char c;         
         for(int i=0; i<81; i++)
         {
            ss >> c;
            if(c >= '1' && c <= '9')
               sudoku[i/9][i%9] = c;
         }
         ss.str(string());

         // solve sudoku
         SimpleSolver solver;
         if(argc == 3) solver.print(sudoku);
         solver.solveSudoku(sudoku);

         if(argc == 3)
         {
            cout << "Solutions:" << endl;
            solver.print(sudoku);
         }
      }//while
      fin.close();
   }
   
   return 0;
}
