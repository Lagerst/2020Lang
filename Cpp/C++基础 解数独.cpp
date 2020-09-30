#include <vector>

using namespace std;

class Solution {
public:
  bool flag = false;
  bool valid(int i, int j, vector<vector<char>> &board) {
    for (int k = 0; k < 9; k++) {
      if (board[i][k] == board[i][j] && k != j) {
        return false;
      }
      if (board[k][j] == board[i][j] && k != i) {
        return false;
      }
    }
    for (int l = i / 3 * 3; l < i / 3 * 3 + 3; l++) {
      for (int r = j / 3 * 3; r < j / 3 * 3 + 3; r++) {
        if (board[l][r] == board[i][j] && !(l == i && r == j)) {
          return false;
        }
      }
    }
    return true;
  }
  void solveSudoku(vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') {
          for (int num = 1; num < 10; num++) {
            if (flag)
              return;
            board[i][j] = num + '0';
            if (valid(i, j, board)) {
              solveSudoku(board);
            } else if (num == 9) {
              board[i][j] = '.';
              return;
            }
            if (num == 9 && !flag) {
              board[i][j] = '.';
              return;
            }
          }
        }
      }
    }
    flag = true;
    return;
  }
};