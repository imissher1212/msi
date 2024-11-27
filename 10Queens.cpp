#include <iostream>
using namespace std;

bool isSafe(int row, int col, int board[10][10], int n) {
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

bool solveNQueensUtil(int board[10][10], int col, int n) {
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

void printSolution(int board[10][10], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

void solveNQueens(int n) {
    int board[10][10] = {0};
    if (solveNQueensUtil(board, 0, n)) {
        printSolution(board, n);
    } else {
        cout << "No solution exists." << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;
    if (n > 10) {
        cout << "This implementation supports up to 10 queens only." << endl;
        return 1;
    }
    solveNQueens(n);
    return 0;
}
