#include "bits/stdc++.h"

using namespace std;

class Board {

private:
    unsigned long board[3][3];
    unsigned long player_ids[2];

public:
    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                board[i][j] = 0;
        }
    }

    bool place_symbol(unsigned long _id, int _row, int _col) {
        if (board[_row][_col] != 0)
            return false;

        board[_row][_col] = _id;
        return true;
    }

    Pair<bool, unsigned long> get_winner() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            unsigned long prev_id = 0;
            bool terminal = true;
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != prev_id && prev_id != 0) {
                    terminal = false;
                    break; 
                }
            }

            if (terminal)
                return true;
        }

        // Check


        return false;
    }

};

int main() {
    int board[9];

    for (int i = 0; i < 9; i++)
        board[i] = 0;

    unsigned long player_ids[2];

    cin >> player_ids[0];
    cin >> player_ids[1];



    cout << player_ids[0];

}