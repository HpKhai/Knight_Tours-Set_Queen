#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cmath>
using namespace std;

#define N 5

bool isSafe(int x, int y, vector<vector<int> >& board) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

void printBoard(vector<vector<int> >& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

bool solveKTUtil(vector<vector<int> >& board, int x, int y, int movei, int xMove[], int yMove[]) {
    int k, next_x, next_y;
    if (movei == 25) // N?u dã di qua h?t các ô
        return true;

    for (k = 0; k < 8; k++) {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y, board)) {
            board[next_x][next_y] = movei;
            if (solveKTUtil(board, next_x, next_y, movei + 1, xMove, yMove))
                return true;
            else
                board[next_x][next_y] = -1;
        }
    }
    return false;
}

vector<vector<int> > solveKT(vector<pair<int, int> >& initialPositions) {
    vector<vector<int> > board(N, vector<int>(N, -1));
    int xMove[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[] = {1, 2, 2, 1, -1, -2, -2, -1};

    int lastKnightIndex = initialPositions.size() - 1;
    int x = initialPositions[lastKnightIndex].first;
    int y = initialPositions[lastKnightIndex].second;

    for (int i = 0; i < initialPositions.size(); ++i) {
        int x = initialPositions[i].first;
        int y = initialPositions[i].second;
        board[x][y] = i;
    }
    int lastKnightValue = lastKnightIndex + 1;

    if (solveKTUtil(board, x, y, lastKnightValue, xMove, yMove)) {
        cout << "This is the solution:" << endl;
        printBoard(board);
        return board;
    }

    cout << "Solution does not exist" << endl;
    return vector<vector<int> >();
}

bool isKnightMove(pair<int, int> pos1, pair<int, int> pos2) {
    int dx = abs(pos1.first - pos2.first);
    int dy = abs(pos1.second - pos2.second);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

int main() {
    vector<pair<int, int> > initialPositions;
    int n;
    cout << "Enter the number of initial knight-positions: ";
    cin >> n;

    cout << "Enter the initial positions (x, y):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Enter the initial positions " << i + 1 << " (x, y): ";
        int x, y;
        cin >> x >> y;
        initialPositions.push_back(make_pair(x, y));
    }

    // G?i hàm d? gi?i quy?t bài toán
    vector<vector<int> > board = solveKT(initialPositions);

    // Ki?m tra t?t c? các v? trí trong m?ng initialPositions có di theo quy t?c quân mã không
    bool validMoves = true;
    for (size_t i = 1; i < initialPositions.size(); ++i) {
        if (!isKnightMove(initialPositions[i - 1], initialPositions[i])) {
            validMoves = false;
            cout << "Invalid knight move from position " << i << " to position " << i + 1 << "." << endl;
        }
    }

    if (validMoves && !board.empty()) {
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

    return 0;
}

