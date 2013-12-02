#include <iostream>
#include "DLX.h"

using namespace std;

void test()
{
   vector<string> el = {"1", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
   vector<vector<string> > rows;
   rows.push_back(vector<string>({"1", "5", "9", "13"}));
   rows.push_back(vector<string>({"3", "8", "10", "16"}));
   rows.push_back(vector<string>({"4", "7", "11", "15"}));

   rows.push_back(vector<string>({"1", "6", "10", "14"}));
   rows.push_back(vector<string>({"3", "7", "9", "15"}));
   rows.push_back(vector<string>({"4", "8", "12", "16"}));

   DLX dlx(el, rows);

   cout << "First solution: " << endl;
   dlx.search();

   cout << "All solution: " << endl;
   dlx.search(true);
   
}

int main(int argc, char *argv[])
{
   vector<string> el = {"A", "B", "C", "D", "E", "F", "G"};
   
   vector<vector<string> > rows;
   rows.push_back(vector<string>({"C", "E", "F"}));
   rows.push_back(vector<string>({"A", "D", "G"}));
   rows.push_back(vector<string>({"B", "C", "F"}));
   rows.push_back(vector<string>({"A", "D"}));
   rows.push_back(vector<string>({"B", "G"}));
   rows.push_back(vector<string>({"D", "E", "G"}));
   rows.push_back(vector<string>({"A", "B", "C"}));
   rows.push_back(vector<string>({"D", "E", "G"}));
   rows.push_back(vector<string>({"F"}));

   DLX dlx(el, rows);
   
   // dlx.printMatrix();
   
   // cout << "first column: " << dlx.getNextColumn() << std::endl;

   // cout << "After cover" << endl;
   // dlx.coverColumn(1);
   // dlx.printMatrix();

   // cout << "After uncover" << endl;
   // dlx.uncoverColumn(1);
   // dlx.printMatrix();

   
   cout << "First solution: " << endl;
   dlx.search();
   dlx.printSolutions(cout);
   
   cout << "All solution: " << endl;
   dlx.search(true);
   dlx.printSolutions(cout);

   return 0;
}

