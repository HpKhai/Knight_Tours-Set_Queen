#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const int N = 8; // K�ch thu?c b�n c?

bool isSafe(vector<vector<int> >& board, int row, int col) {
    // Ki?m tra h�ng ngang
    for (int i = 0; i < N; i++)
        if (board[row][i] != 0 && i != col) // B? qua � ch?a qu�n h?u tr? � hi?n t?i
            return false;

    // Ki?m tra c?t d?c
    for (int i = 0; i < N; i++)
        if (board[i][col] != 0 && i != row) // B? qua � ch?a qu�n h?u tr? � hi?n t?i
            return false;

    // Ki?m tra du?ng ch�o tr�n b�n tr�i
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] != 0)
            return false;

    // Ki?m tra du?ng ch�o du?i b�n tr�i
    for (int i = row + 1, j = col - 1; i < N && j >= 0; i++, j--)
        if (board[i][j] != 0)
            return false;

    // Ki?m tra du?ng ch�o tr�n b�n ph?i
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j] != 0)
            return false;

    // Ki?m tra du?ng ch�o du?i b�n ph?i
    for (int i = row + 1, j = col + 1; i < N && j < N; i++, j++)
        if (board[i][j] != 0)
            return false;

    return true;
}


// H�m d?t tru?c qu�n h?u
void prePlaceQueens(vector<vector<int> >& board) {
    int numQueens;
    cout << "Enter the quantity of military forces you wish to deploy. ";
    cin >> numQueens;
    if (numQueens != 0 && numQueens < 9) {
        for (int i = 0; i < numQueens; i++) {
            int row, col;
            cout << "The position of the military forces " << i + 1 << " (x y):" << endl;
            cin >> row >> col;
            // Ki?m tra n?u v? tr� nh?p v�o h?p l?
            if (row >= 0 && row < N && col >= 0 && col < N) {
                board[row][col] = i + 1; // S? th? t? c?a qu�n h?u l� i+1
            } else {
                cout << "The position is not suitable, please re-enter." << endl;
                i--; // �?m b?o s? lu?ng qu�n h?u nh?p d�ng sau m?i l?n l?p
            }
        }
    }
}

bool solveNQueensUtil(vector<vector<int> >& board, int n, int& placedQueens) {
    // N?u d� d?t h?t qu�n h?u
    if (placedQueens == N)
        return true;

    // Th? t?ng � trong h�ng hi?n t?i
    for (int i = 0; i < N; i++) {
        // Ki?m tra xem � (n, i) c� th? d?t qu�n h?u du?c kh�ng
        if (isSafe(board, n, i)) {
            // �?t qu�n h?u t?i � (n, i)
            board[n][i] = placedQueens + 1; // S? th? t? c?a qu�n h?u l� placedQueens + 1
            placedQueens++; // Tang s? lu?ng qu�n h?u d� d?t

            // �? quy d?t qu�n h?u v�o c?t ti?p theo
            if (solveNQueensUtil(board, n + 1, placedQueens))
                return true;

            // N?u kh�ng th? d?t qu�n h?u t?i � n�y, th� quay lui v� th? � kh�c
            board[n][i] = 0;
            placedQueens--; // Gi?m s? lu?ng qu�n h?u d� d?t
        }
    }
    // N?u kh�ng t�m du?c v? tr� ph� h?p cho qu�n h?u trong h�ng hi?n t?i
    return false;
}

// H�m ch�nh d? gi?i b�i to�n
void solveNQueens() {
    vector<vector<int> > board(N, vector<int>(N, 0));
    int placedQueens = 0; // Bi?n d?m s? qu�n h?u d� d?t

    // �?t tru?c qu�n h?u n?u c�
    prePlaceQueens(board);

    if (solveNQueensUtil(board, 0, placedQueens) == false) {
        cout << "Solution does not exist!" << endl;
        return;
    }

    // N?u d� 8 qu�n h?u m?i in b�n c?
    if (placedQueens == N) {
        // In ra b�n c? sau khi d?t qu�n h?u
        cout << "The board after deploying the military forces:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        ofstream outFile("solution-boardQueen.txt");
        if (outFile.is_open()) {
            // Ghi b�n c? v�o t?p tin
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    outFile << board[i][j] << "\t";
                }
                outFile << endl;
            }
            // ��ng t?p tin
            outFile.close();
            cout << "The chessboard has been recorded in the file solution-boardQueen.txt." << endl;
    	}
	}
}

int main() {
    solveNQueens();
    return 0;
}

