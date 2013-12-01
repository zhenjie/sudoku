#include <iostream>
#include "dlx.h"

using namespace std;

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
   dlx.search(false);

   cout << "All solution: " << endl;
   dlx.search(true);

   return 0;
}
