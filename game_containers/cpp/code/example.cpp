#include "bits/stdc++.h"
#include <sys/select.h>

using namespace std;

#define START_TOKEN 0xFFFFFFFF

class Board {

private:
    unsigned long board[3][3];
    unsigned long player_ids[2];

public:
    Board(unsigned long _id1, unsigned long _id2) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                board[i][j] = 0;
        }

        player_ids[0] = _id1;
        player_ids[1] = _id2;
    }

    bool play_move(pair<int, int> _loc, unsigned long _id) {
        if (_loc.first < 0 || _loc.first > 2 || _loc.second < 0 || _loc.second > 2 || board[_loc.first][_loc.second] != 0)
            return false;

        board[_loc.first][_loc.second] = _id;
        return true;
    }

    pair<bool, unsigned long> get_winner() {
        
        int available_spots = 0;

        for (int i = 0; i < 3; i++) {
            // -1 = 0xFFFFFFFF right...? 
            // Anyway, want starting token to be different from default board val (i.e. 0)
            unsigned long row_prev_id = START_TOKEN;
            unsigned long col_prev_id = START_TOKEN;
            unsigned long dia_prev_id1 = START_TOKEN;
            unsigned long dia_prev_id2 = START_TOKEN;

            bool row_terminal = true;
            bool col_terminal = true;
            bool dia1_terminal = true;
            bool dia2_terminal = true;

            for (int j = 0; j < 3; j++) {

                if (board[i][j] == 0)
                    available_spots++;


                if ((board[i][j] != row_prev_id && row_prev_id != START_TOKEN) || row_prev_id == 0)
                    row_terminal = false;

                if ((board[j][i] != col_prev_id && col_prev_id != START_TOKEN) || col_prev_id == 0)
                    col_terminal = false;

                if ((board[j][j] != dia_prev_id1 && dia_prev_id1 != START_TOKEN) || dia_prev_id1 == 0)
                    dia1_terminal = false;
                
                if ((board[j][2-j] != dia_prev_id2 && dia_prev_id2 != START_TOKEN) || dia_prev_id2 == 0)
                    dia2_terminal = false;

                
                row_prev_id = board[i][j];
                col_prev_id = board[j][i];
                dia_prev_id1 = board[j][j];
                dia_prev_id2 = board[j][2-j];
            }

            if (row_terminal) 
                return { true, row_prev_id };

            if (col_terminal)
                return { true, col_prev_id };

            if (dia1_terminal) 
                return { true, dia_prev_id1 };

            if (dia2_terminal)
                return { true, dia_prev_id2 };
        }

        return { false,  available_spots };
    }

    void print() {
        cout << "-----------" << endl;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == player_ids[0] && j != 2) {
                    cout << " X |";
                } else if (board[i][j] == player_ids[0]) {
                    cout << " X";
                } else if (board[i][j] == player_ids[1] && j != 2) {
                    cout << " O |";
                } else if (board[i][j] == player_ids[1]) {
                    cout << " O";
                } else if (j != 2) {
                    cout << "   |";
                } 
            }
            cout << endl;

            cout << "-----------" << endl;
        }

    }

};

pair<int, int> listen_for_move(unsigned long id) {

    int row, col;
    cin >> row >> col;
    return { row, col };
    
}

int main() {
    unsigned long player_ids[2];

    cin >> player_ids[0];
    cin >> player_ids[1];


    Board b = Board(player_ids[0], player_ids[1]);

    int cur_i = 0;
    pair<int, int> move;
    while(true) {
        b.print();
        move = listen_for_move(player_ids[cur_i]);
        if (!b.play_move(move, player_ids[cur_i])) {
            cout << "TG ERROR: Invalid Move" << endl;
            cout << "PLAYER ID: " << player_ids[cur_i] << endl;
            cout << "Values: (row: " << move.first << ", col: " << move.second << ")" << endl;
            return -1;
        }

        if (b.get_winner().first) {
            cout << "TG RESULT: WIN" << endl;
            cout << "PLAYER ID: " << player_ids[cur_i] << endl;
            b.print();
            return 0;
        } else if (b.get_winner().second == 0) {
            cout << "TG RESULT: Draw" << endl;
            b.print();
            return 0;
        }
        cur_i ^= 1;
    }   

}