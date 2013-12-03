sudoku
======

It's not just about Sudoku Solver, it's about using DLX to solve other interesting problems. 


simple instruction
==================

Make sure you know how to print "Hello World!" in C++.

The DLX is implement as class DLX every other solver class will call DLX to solve the underlying exact cover problem. The solution returned by DLX is vector<vector<size_t> > _solutions where every row represents a solution for the problem. Each element(i) of a solution corresponds to the index in the vector<vector<string> > _rows. 

For example,
   vector<string> el = {"A", "B", "C", "D", "E", "F", "G"};
   vector<vector<string> > rows;
   rows.push_back(vector<string>({"C", "E", "F"})); // set 1
   rows.push_back(vector<string>({"A", "D", "G"})); // set 2
   rows.push_back(vector<string>({"B", "C", "F"})); // set 3
   rows.push_back(vector<string>({"A", "D"}));      // set 4
   rows.push_back(vector<string>({"B", "G"}));      // set 5
   rows.push_back(vector<string>({"D", "E", "G"})); // set 6
   rows.push_back(vector<string>({"A", "B", "C"})); // set 7
   rows.push_back(vector<string>({"D", "E", "G"})); // set 8
   rows.push_back(vector<string>({"F"}));           // set 9
It represents an exact cover problem with 9 sets. We need to find a subset of the 9 sets to cover all the elements.

The solution return by DLX would be,
First solution: 
4 1 5 
All solution: 
4 1 5 
7 9 6 
7 9 8 

Every solution can cover all the elements.



class Solution is a pure virtual class which will be inheritated by specific problem class. You can define your own data member for you inheritated Solution class. For sudoku solver, we defined class SudokuSolution which contains one data member: vector<vector<int> > _solution. You need to implement a function to take the return of DLX as input and parse them into your own Solution representation. 

class Solver is another pure virtual class which will be inheritated by specific problem class. It shares three members with it's inheritated classes, i.e.,
    bool _all;    // find all solution?
    bool _found;  // found any solution?
    bool _solved; // is this puzzle solved?

You have to implement the interface in your Solver to make rows and elements and pass them to DLX. It's also your job to set up the solutions through your inheritated Solution class. For the sudoku solver, we defined class SudokuSolver which will load data from memory or file, ake rows as well as elements, pass them to DLX, make solutions using the constructor of SudokuSolution. 


Other interesting puzzle?
=========================
If these puzzle can be solved by exact cover, then it can be solved by our library. Take N-Queen as example,

We can define two classes, 
    class NQueenSolver : public Solver{}
    class NQueenSolution : public Solution{}
    
Implement the interface *load*, *makeRows*, *makeElements*, *makeSolutions*, etc.




