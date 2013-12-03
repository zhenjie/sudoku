/**
 * @file   test.cpp
 * @author Zhenjie Chen <zhenjie@mail.ustc.edu.cn>
 * @date   Tue Dec  3 10:36:25 2013
 * 
 * @brief  Simple test file.
 * 
 * To compile:
 ```
 g++ -std=c++11  ../PentominoesSolution.cpp ../PentominoesSolver.cpp ../../DLX.cpp   -I.. -I../.. test.cpp
 ```
 */

#include <iostream>
#include "PentominoesSolver.h"


int main(int argc, char *argv[])
{
   PentominoesSolver ps(3, 20);
   if( ps.solve() ) 
      std::cout << "Found solution:" << std::endl;
   else
      std::cout << "No solution!" << std::endl;

   auto slt = ps.getOneSolution();
   slt->printSolution();


   ps.clear();
   ps.set_row_column(4, 15);
   if( ps.solve() ) 
      std::cout << "Found solution:" << std::endl;
   else
      std::cout << "No solution!" << std::endl;
   slt = ps.getOneSolution();
   slt->printSolution();

   ps.clear();
   ps.set_row_column(5, 12);
   if( ps.solve() ) 
      std::cout << "Found solution:" << std::endl;
   else
      std::cout << "No solution!" << std::endl;
   slt = ps.getOneSolution();
   slt->printSolution();


   ps.clear();
   ps.set_row_column(6, 10);
   if( ps.solve() ) 
      std::cout << "Found solution:" << std::endl;
   else
      std::cout << "No solution!" << std::endl;
   slt = ps.getOneSolution();
   slt->printSolution();

   
   
   return 0;
}
