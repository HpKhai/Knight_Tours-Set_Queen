#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

// K�ch thu?c c?a b?ng
#define N 5

// H�m ki?m tra xem � (x, y) c� n?m trong b?ng v� chua du?c di qua chua
bool isSafe(int x, int y, vector<vector<int> >& board) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

// In b?ng ra m�n h�nh
void printBoard(vector<vector<int> >& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

// H�m gi?i b�i to�n di tu?n c?a qu�n m�
bool solveKTUtil(vector<vector<int> >& board, int x, int y, int movei, int xMove[], int yMove[]) {
    int k, next_x, next_y;
    if (movei == N * N  ) // N?u d� di qua h?t c�c �
        return true;

    // Th? t?t c? c�c bu?c di chuy?n ti?p theo t? (x, y)
    for (k = 0; k < 8; k++) {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y, board)) {
            board[next_x][next_y] = movei;
            if (solveKTUtil(board, next_x, next_y, movei + 1, xMove, yMove))
                return true;
            else
                board[next_x][next_y] = -1; // N?u kh�ng th�nh c�ng, d�nh d?u � n�y chua di qua
        }
    }
    return false;
}


bool solveKT(vector<pair<int, int> >& initialPositions) {
    vector<vector<int> > board(N, vector<int>(N, -1)); // Kh?i t?o b?ng
    // C�c bu?c di chuy?n c?a qu�n m�
    int xMove[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[] = {1, 2, 2, 1, -1, -2, -2, -1};

	// L?y gi� tr? c?a qu�n h?u cu?i c�ng t? danh s�ch initialPositions
    int lastKnightIndex = initialPositions.size() - 1;
    int x = initialPositions[lastKnightIndex].first;
    int y = initialPositions[lastKnightIndex].second;
	
    // ��nh d?u t?t c? c�c � d� du?c d?t qu�n m� tru?c d� l� d� di qua
    for (int i = 0; i < initialPositions.size(); ++i) {
        int x = initialPositions[i].first;
        int y = initialPositions[i].second;
        board[x][y] = i; // Gi� tr? c?a qu�n m� l� s? th? t? c?a n� trong danh s�ch initialPositions
    }
	int lastKnightValue =lastKnightIndex + 1;
//	printBoard(board);
    // Th? gi?i b�i to�n di tu?n t? qu�n h?u cu?i c�ng du?c nh?p v�o
    if (solveKTUtil(board, x, y, lastKnightValue, xMove, yMove)) {
    	cout<<"This is solutions!"<<endl;
        printBoard(board);
        ofstream outFile("solution-boardKningt.txt");
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
            cout << "The chessboard has been recorded in the file solution-boardKningt.txt." << endl;
    	}
        return true;
    }

    cout << "Solution does not exist";
    return false;
}

// H�m main
int main() {
    int n;
    cout << "Enter the number of initial knight-positions: ";
    cin >> n;

    vector<pair<int, int> > initialPositions;
//    cout << "Enter the initial positions (x, y):" << endl;
    for (int i = 0; i < n; i++) {
    	cout << "Enter the initial positions "<< i+1 <<" (x, y):" << endl;
        int x, y;
        cin >> x >> y;
        initialPositions.push_back(make_pair(x, y));
    }

    solveKT(initialPositions);
    return 0;
}

