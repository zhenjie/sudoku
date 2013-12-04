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


void test(int row = 6, int column = 10)
{
   PentominoesSolver ps(row, column);
   if( ps.solve() ) 
      std::cout << "Found solution:" << std::endl;
   else
      std::cout << "No solution!" << std::endl;

   auto slt = ps.getOneSolution();
   slt->printSolution();
}

int main(int argc, char *argv[])
{
   test(3, 20);
   test(4, 15);
   test(5, 12);
   test(6, 10);
   test(20, 3);
   test(15, 4);
   test(12, 5);
   test(10, 6);

   return 0;
}
