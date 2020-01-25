#include "move.h"

#include <ncurses.h>

int move_loop(WINDOW *dialogue_window, int **board, const int BOARD_ROWS, const int BOARD_COLS, int player) {
    int valid_move = 0;
    int x, y;

    while ( !valid_move ) {
        x = wgetch(dialogue_window) - '0' - 1; // get char '1'-'7' and convert to int of value 0-7
        if ( x >= 0 && x < BOARD_COLS ) {
            y = player_move(board, BOARD_ROWS, player, x);
            if ( y > -1 )
                valid_move = 1;
        }
    }
    return check_all_wins(board, BOARD_ROWS, BOARD_COLS, x, y);
}

int player_move(int **board, const int BOARD_ROWS, int player, int x) {
    int y;

    for (y = 0; y < BOARD_ROWS; y++) {
        if (board[y][x] == 0) {
            board[y][x] = player;
            return y;
        }
    }
    return -1;
}

int check_all_wins(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y) {
    int dir_x, dir_y;

    int dirs[4][2] = {
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1}
    };

    int dir;
    for (dir = 0; dir < 4; dir++) {
        dir_x = dirs[dir][0];
        dir_y = dirs[dir][1];
        if ((check_win(board, BOARD_ROWS, BOARD_COLS, x, y, dir_x, dir_y, 1) + check_win(board, BOARD_ROWS, BOARD_COLS, x, y, -dir_x, -dir_y, 0)) >= 4)
            return 1;
    }
    return 0;
}

int check_win(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y, int dir_x, int dir_y, int inarow) {
    // Recusively crawls from (x, y) in direction (dir_x, dir_y) until...
    if (
        x + dir_x < 0 ||                // hits left side of board, no win
        x + dir_x > (BOARD_COLS - 1) ||   // hits right side of board, no win
        y + dir_y < 0 ||                // hits bottom of board, no win
        y + dir_y > (BOARD_ROWS - 1)      // hits top of board, no win
       ) {
        return inarow;
    } else if ( board[y][x] != board[y + dir_y][x + dir_x] ) { // hits empty or opposing players square, no win
        return inarow;
    } else {
        inarow = check_win(board, BOARD_ROWS, BOARD_COLS, x+dir_x, y+dir_y, dir_x, dir_y, inarow + 1); // check next square and increment inarow counter
    }
}
