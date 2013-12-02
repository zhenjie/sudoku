#include <iostream> 
#include <unordered_map>
#include <sstream>

#include "SudokuSolution.h"
#include "SudokuSolver.h"

using namespace std;

int main(int argc, char *argv[])
{
   cout << "sudoku 1:" << endl;
   SudokuSolver solver(3, 3, true);
   solver.load("9x9v2");
   solver.print_m();
   solver.solve();

   vector<Solution*> slts = solver.getSolutions();
   cout << "size: " << slts.size() << endl;
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
   solver.clear();
   solver.set_row_column(2, 5);
   solver.set_find_all(true);
   solver.set_stringMap(map);
   solver.load("2x5");
   solver.print_m();
   solver.solve();
   slts = solver.getSolutions();
   for(auto e: slts)
      e->printSolution();
   
   cout << "sudoku 3:" << endl;
   solver.clear();
   cout << "size: " << slts.size() << endl;
   solver.set_row_column(2, 2);
   solver.load("2x2");
   solver.print_m();
   solver.solve();
   slts.clear();
   slts = solver.getSolutions();
   for(auto e: slts)
      e->printSolution();
   
   // cout << "sudoku 4:" << endl;
   // SudokuSolver solver4(1, 2);
   // solver4.load("1x2");
   // solver4.print_m();
   // solver4.solve();

   return 0;
}
