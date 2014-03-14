#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class SimpleSolver
{
public:

    void solveSudoku(vector<vector<char> > &board) {
        solveSudoku(board, 0, 0);
    }
    
    bool solveSudoku(vector<vector<char> > &B, int i, int j){
        if(i > 8) return true;
        if(B[i][j] != '.') return solveSudoku(B, i+(j+1)/9, (j+1)%9);
        
        int r = i/3, c = j/3;
        
        set<char> val;
        for(int k=0; k<9; k++) 
            val.insert({B[i][k], B[k][j], B[r*3 + k/3][c*3 + k%3]});
        
        for(char t='1'; t<='9'; t++)
        {
            if(val.find(t) == val.end())
            {
                B[i][j] = t;
                if(solveSudoku(B, i, j)) return true;
                B[i][j] = '.';
            }
        }
        
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

// int main()
// {
//     SimpleSolver slt;
//     slt.test();
// }
