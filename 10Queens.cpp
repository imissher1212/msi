#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int row, int col, vector<vector<int> >& board, int n) {
    for (int i = 0; i < col; i++) {
        if (board[row][i] == 1) {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    return true;
}

bool solveNQueensUtil(vector<vector<int> >& board, int col, int n) {
    if (col >= n) {
        return true;
    }
    for (int i = 0; i < n; i++) {
        if (isSafe(i, col, board, n)) {
            board[i][col] = 1;
            if (solveNQueensUtil(board, col + 1, n)) {
                return true;
            }
            board[i][col] = 0;
        }
    }
    return false;
}

void printSolution(const vector<vector<int> >& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

void solveNQueens(int n) {
    vector<vector<int> > board(n, vector<int>(n, 0));
    if (solveNQueensUtil(board, 0, n)) {
        printSolution(board);
    } else {
        cout << "No solution exists." << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;
    solveNQueens(n);
    return 0;
}
