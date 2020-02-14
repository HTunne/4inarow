#include "move.h"

#include <stdbool.h>
#include <ncurses.h>
#include "print.h"

enum win_conditions move_loop(WINDOW *dialogue_window, int **board, const int board_rows, const int board_cols, const enum players player) {

    // Check the board isn't full
    bool its_a_draw = true;
    for (int col = 0; col < board_cols; col++) {
        if (board[board_rows - 1][col] == 0) {
            its_a_draw = false; // Empty square found, it's not a draw
            break;
        }
    }
    if (its_a_draw) {
        return Draw;
    }

    int x, y;
    char input;
    bool valid_move = false;
    while ( !valid_move ) {
        input = wgetch(dialogue_window); // get char '1'-'7' and convert to int of value 0-7
        if (input == 'r')
            return Reset;

        x = input - '0' - 1;
        if ( x >= 0 && x < board_cols ) {
            y = player_move(board, board_rows, player, x);
            if ( y > -1 )
                valid_move = true;
        }
    }
    return check_all_wins(board, board_rows, board_cols, x, y);
}

int player_move(int **board, const int board_rows, const enum players player, const int x) {
    int y;

    for (y = 0; y < board_rows; y++) {
        if (board[y][x] == 0) {
            board[y][x] = player;
            return y;
        }
    }
    return -1;
}

enum win_conditions check_all_wins(int **board, const int board_rows, const int board_cols, const int x, const int y) {
    int dir_x, dir_y;

    // Directions in (x,y) to check
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

        // Check squares in a row in opposing directions
        if ((check_win(board, board_rows, board_cols, x, y, dir_x, dir_y, 1) + check_win(board, board_rows, board_cols, x, y, -dir_x, -dir_y, 0)) >= 4)
            return Win; // win
    }
    return No_Win; // no win
}

int check_win(int **board, const int board_rows, const int board_cols, const int x, const int y, const int dir_x, const int dir_y, int inarow) {
    // Recusively crawls from (x, y) in direction (dir_x, dir_y) until...
    if (
        x + dir_x < 0 ||                            // hits left side of board, no win
        x + dir_x > (board_cols - 1) ||             // hits right side of board, no win
        y + dir_y < 0 ||                            // hits bottom of board, no win
        y + dir_y > (board_rows - 1) ||             // hits top of board, no win
        board[y][x] != board[y + dir_y][x + dir_x]  // hits empty or opposing players square, no win
       ) {
        return inarow;
    } else {
        return check_win(board, board_rows, board_cols, x+dir_x, y+dir_y, dir_x, dir_y, inarow + 1); // check next square and increment inarow counter
    }
}

