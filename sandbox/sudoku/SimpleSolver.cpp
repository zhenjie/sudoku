#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class SimpleSolver
{
public:
   void solveSudoku(vector<vector<char> > &board) {
      // naive backtrack
        
      const int N = 9;
      for(int i=0; i<N; i++)
      {
         for(int j=0; j<N; j++)
         {
            if(board[i][j] == '.')
            {
               solveSudoku(board, i, j);
               return;
            }
         }
      }//for
        
      return;
   }
    
   bool solveSudoku(vector<vector<char> > &board, int i, int j) {
      if(i*9+j == 81) return true; // finished

      // board[i][j] is empty cell
      // for every possible value in board[i][j], do recursive call with i' and j'
      vector<bool> val(10, true);

      // check ith row, jth column, and block containing i, j
      int bi = i/3, bj = j/3;
      for(int e=0; e<9; e++)
      {
         // cout << board[i][e] << " " << board[e][j] << endl;
         if( board[i][e] != '.' ) val[ board[i][e] - '0' ] = false; 
         if( board[e][j] != '.' ) val[ board[e][j] - '0' ] = false; 
      }
      for(int r=bi*3; r<bi*3+3; r++)
         for(int c=bj*3; c<bj*3+3; c++)
         {
            if( board[r][c] != '.') val[ board[r][c] - '0' ] = false; 
         }

      // find new i, j
      int ii, jj;
      int n = i*9+j+1;
      ii = n/9; 
      jj = n%9;
      while(n < 81)
      {
         ii = n/9; jj = n%9;
         if(board[ii][jj] == '.') break;
         n++;
      }

      for(int k=1; k<10; k++)
      {
         if(val[k]) 
         {
            // cout << "set " << k << " at [" << i << ", " << j << "]" <<  endl;
            board[i][j] = k + '0';
            if(n == 81) return true; // finished

            if( solveSudoku(board, ii, jj) ) return true;
            else board[i][j] = '.';
         }
      }//for
        
      // if board[i, j] is not set, and we can not find possible ways
      return false;
   }

   void print(vector<vector<char> > &board)
      {
         for(auto e: board)
         {
            for(auto i: e)
               cout << i << " ";
      
            cout << endl;
         }
      }

   int test()
      {
         vector<vector<char> > board0 ({
               vector<char>({'.', '.', '9', '7', '4', '8', '.', '.', '.'}), 
                  vector<char>({'7', '.', '.', '.', '.', '.', '.', '.', '.'}), 
                  vector<char>({'.', '2', '.', '1', '.', '9', '.', '.', '.'}), 
                  vector<char>({'.', '.', '7', '.', '.', '.', '2', '4', '.'}), 
                  vector<char>({'.', '6', '4', '.', '1', '.', '5', '9', '.'}), 
                  vector<char>({'.', '9', '8', '.', '.', '.', '3', '.', '.'}), 
                  vector<char>({'.', '.', '.', '8', '.', '3', '.', '2', '.'}), 
                  vector<char>({'.', '.', '.', '.', '.', '.', '.', '.', '6'}), 
                  vector<char>({'.', '.', '.', '2', '7', '5', '9', '.', '.'})
                  });

         vector<vector<char> > board ({
               vector<char>({'5', '3', '.', '.', '7', '.', '.', '.', '.'}), 
                  vector<char>({'6', '.', '.', '1', '9', '5', '.', '.', '.'}), 
                  vector<char>({'.', '9', '8', '.', '.', '.', '.', '6', '.'}), 
                  vector<char>({'8', '.', '.', '.', '6', '.', '.', '.', '3'}), 
                  vector<char>({'4', '.', '.', '8', '.', '3', '.', '.', '1'}), 
                  vector<char>({'7', '.', '.', '.', '2', '.', '.', '.', '6'}), 
                  vector<char>({'.', '6', '.', '.', '.', '.', '2', '8', '.'}), 
                  vector<char>({'.', '.', '.', '4', '1', '9', '.', '.', '5'}),
                  vector<char>({'.', '.', '.', '.', '8', '.', '.', '7', '9'})
                  });
   
         SimpleSolver slt;

         cout << "Original" << endl;
         slt.print(board);
   
         slt.solveSudoku(board);
   
         cout << "Solution" << endl;
         slt.print(board);
         return 0;
      }
};

