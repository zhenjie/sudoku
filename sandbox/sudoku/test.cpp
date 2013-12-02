#include <iostream>
#include <unordered_map>
#include <sstream>

#include "SudokuSolution.h"
#include "SudokuSolver.h"
#include "Solution.h"

using namespace std;

int main(int argc, char *argv[])
{
   cout << "sudoku 1:" << endl;
   SudokuSolver solver(3, 3, true);
   solver.load("9x9");
   solver.print_m();
   solver.solve();

   vector<Solution*> slts = solver.getSolutions();
   for(auto e: slts)
      e->printSolution();

   unordered_map<string, int> map;
   stringstream ss;
   for(int i=0; i<=9; i++)
   {
      ss << i;
      map[ss.str()] = i;
      ss.str(string());
   }
   map["A"] = 10;

   cout << "sudoku 2:" << endl;
   SudokuSolver solver2(map, 2, 5, true);
   solver2.load("2x5");
   solver2.print_m();
   solver2.solve();

   cout << "sudoku 3:" << endl;
   SudokuSolver solver3(2, 2);
   solver3.load("2x2");
   solver3.print_m();
   solver3.solve();

   cout << "sudoku 4:" << endl;
   SudokuSolver solver4(1, 2);
   solver4.load("1x2");
   solver4.print_m();
   solver4.solve();

   return 0;
}