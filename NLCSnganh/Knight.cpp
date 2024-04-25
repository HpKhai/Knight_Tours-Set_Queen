#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

// Kích thu?c c?a b?ng
#define N 5

// Hàm ki?m tra xem ô (x, y) có n?m trong b?ng và chua du?c di qua chua
bool isSafe(int x, int y, vector<vector<int> >& board) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

// In b?ng ra màn hình
void printBoard(vector<vector<int> >& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

// Hàm gi?i bài toán di tu?n c?a quân mã
bool solveKTUtil(vector<vector<int> >& board, int x, int y, int movei, int xMove[], int yMove[]) {
    int k, next_x, next_y;
    if (movei == N * N  ) // N?u dã di qua h?t các ô
        return true;

    // Th? t?t c? các bu?c di chuy?n ti?p theo t? (x, y)
    for (k = 0; k < 8; k++) {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y, board)) {
            board[next_x][next_y] = movei;
            if (solveKTUtil(board, next_x, next_y, movei + 1, xMove, yMove))
                return true;
            else
                board[next_x][next_y] = -1; // N?u không thành công, dánh d?u ô này chua di qua
        }
    }
    return false;
}


bool solveKT(vector<pair<int, int> >& initialPositions) {
    vector<vector<int> > board(N, vector<int>(N, -1)); // Kh?i t?o b?ng
    // Các bu?c di chuy?n c?a quân mã
    int xMove[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[] = {1, 2, 2, 1, -1, -2, -2, -1};

	// L?y giá tr? c?a quân h?u cu?i cùng t? danh sách initialPositions
    int lastKnightIndex = initialPositions.size() - 1;
    int x = initialPositions[lastKnightIndex].first;
    int y = initialPositions[lastKnightIndex].second;
	
    // Ðánh d?u t?t c? các ô dã du?c d?t quân mã tru?c dó là dã di qua
    for (int i = 0; i < initialPositions.size(); ++i) {
        int x = initialPositions[i].first;
        int y = initialPositions[i].second;
        board[x][y] = i; // Giá tr? c?a quân mã là s? th? t? c?a nó trong danh sách initialPositions
    }
	int lastKnightValue =lastKnightIndex + 1;
//	printBoard(board);
    // Th? gi?i bài toán di tu?n t? quân h?u cu?i cùng du?c nh?p vào
    if (solveKTUtil(board, x, y, lastKnightValue, xMove, yMove)) {
    	cout<<"This is solutions!"<<endl;
        printBoard(board);
        ofstream outFile("solution-boardKningt.txt");
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
            cout << "The chessboard has been recorded in the file solution-boardKningt.txt." << endl;
    	}
        return true;
    }

    cout << "Solution does not exist";
    return false;
}

// Hàm main
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

