#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const int N = 8; // Kích thu?c bàn c?

bool isSafe(vector<vector<int> >& board, int row, int col) {
    // Ki?m tra hàng ngang
    for (int i = 0; i < N; i++)
        if (board[row][i] != 0 && i != col) // B? qua ô ch?a quân h?u tr? ô hi?n t?i
            return false;

    // Ki?m tra c?t d?c
    for (int i = 0; i < N; i++)
        if (board[i][col] != 0 && i != row) // B? qua ô ch?a quân h?u tr? ô hi?n t?i
            return false;

    // Ki?m tra du?ng chéo trên bên trái
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] != 0)
            return false;

    // Ki?m tra du?ng chéo du?i bên trái
    for (int i = row + 1, j = col - 1; i < N && j >= 0; i++, j--)
        if (board[i][j] != 0)
            return false;

    // Ki?m tra du?ng chéo trên bên ph?i
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j] != 0)
            return false;

    // Ki?m tra du?ng chéo du?i bên ph?i
    for (int i = row + 1, j = col + 1; i < N && j < N; i++, j++)
        if (board[i][j] != 0)
            return false;

    return true;
}


// Hàm d?t tru?c quân h?u
void prePlaceQueens(vector<vector<int> >& board) {
    int numQueens;
    cout << "Enter the quantity of military forces you wish to deploy. ";
    cin >> numQueens;
    if (numQueens != 0 && numQueens < 9) {
        for (int i = 0; i < numQueens; i++) {
            int row, col;
            cout << "The position of the military forces " << i + 1 << " (x y):" << endl;
            cin >> row >> col;
            // Ki?m tra n?u v? trí nh?p vào h?p l?
            if (row >= 0 && row < N && col >= 0 && col < N) {
                board[row][col] = i + 1; // S? th? t? c?a quân h?u là i+1
            } else {
                cout << "The position is not suitable, please re-enter." << endl;
                i--; // Ð?m b?o s? lu?ng quân h?u nh?p dúng sau m?i l?n l?p
            }
        }
    }
}

bool solveNQueensUtil(vector<vector<int> >& board, int n, int& placedQueens) {
    // N?u dã d?t h?t quân h?u
    if (placedQueens == N)
        return true;

    // Th? t?ng ô trong hàng hi?n t?i
    for (int i = 0; i < N; i++) {
        // Ki?m tra xem ô (n, i) có th? d?t quân h?u du?c không
        if (isSafe(board, n, i)) {
            // Ð?t quân h?u t?i ô (n, i)
            board[n][i] = placedQueens + 1; // S? th? t? c?a quân h?u là placedQueens + 1
            placedQueens++; // Tang s? lu?ng quân h?u dã d?t

            // Ð? quy d?t quân h?u vào c?t ti?p theo
            if (solveNQueensUtil(board, n + 1, placedQueens))
                return true;

            // N?u không th? d?t quân h?u t?i ô này, thì quay lui và th? ô khác
            board[n][i] = 0;
            placedQueens--; // Gi?m s? lu?ng quân h?u dã d?t
        }
    }
    // N?u không tìm du?c v? trí phù h?p cho quân h?u trong hàng hi?n t?i
    return false;
}

// Hàm chính d? gi?i bài toán
void solveNQueens() {
    vector<vector<int> > board(N, vector<int>(N, 0));
    int placedQueens = 0; // Bi?n d?m s? quân h?u dã d?t

    // Ð?t tru?c quân h?u n?u có
    prePlaceQueens(board);

    if (solveNQueensUtil(board, 0, placedQueens) == false) {
        cout << "Solution does not exist!" << endl;
        return;
    }

    // N?u dã 8 quân h?u m?i in bàn c?
    if (placedQueens == N) {
        // In ra bàn c? sau khi d?t quân h?u
        cout << "The board after deploying the military forces:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        ofstream outFile("solution-boardQueen.txt");
        if (outFile.is_open()) {
            // Ghi bàn c? vào t?p tin
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    outFile << board[i][j] << "\t";
                }
                outFile << endl;
            }
            // Ðóng t?p tin
            outFile.close();
            cout << "The chessboard has been recorded in the file solution-boardQueen.txt." << endl;
    	}
	}
}

int main() {
    solveNQueens();
    return 0;
}

