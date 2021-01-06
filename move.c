#include "move.h"

#include <stdbool.h>
#include <ncurses.h>
#include "print.h"

enum win_conditions move_loop(WINDOW *dialogue_window, enum players **board, const uint8_t board_rows, const uint8_t board_cols, const enum players player) {

    if (is_draw(board, board_rows, board_cols)) {
        return Draw;
    }

    int8_t x, y;
    uint8_t input;
    while (true) {
        input = wgetch(dialogue_window); // get char '1'-'7' and convert to int of value 0-7
        if (input == 'r')
            return Reset;

        x = input - '0' - 1;
        if ( x >= 0 && x < board_cols ) {
            y = player_move(board, board_rows, player, x);
            if ( y > -1 )
                break;
        }
    }
    return check_all_wins(board, board_rows, board_cols, x, y);
}

bool is_draw(enum players **board, const uint8_t board_rows, const uint8_t board_cols) {
    // Check the board isn't full
    for (uint8_t col = 0; col < board_cols; col++) {
        if (board[board_rows - 1][col] == 0) {
            return false;
        }
    }
    return true;
}


int8_t player_move(enum players **board, const uint8_t board_rows, const enum players player, const uint8_t x) {
    for (uint8_t y = 0; y < board_rows; y++) {
        if (board[y][x] == 0) {
            board[y][x] = player;
            return y;
        }
    }
    return -1;
}

enum win_conditions check_all_wins(enum players **board, const uint8_t board_rows, const uint8_t board_cols, const uint8_t x, const uint8_t y) {

    // Directions in (x,y) to check
    int8_t dirs[4][2] = {
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1}
    };

    for (int8_t dir = 0; dir < 4; dir++) {
        // Check squares in a row in opposing directions
        if ((check_win(board, board_rows, board_cols, x, y, dirs[dir][0], dirs[dir][1], 1) + // check win in +ve dir
             check_win(board, board_rows, board_cols, x, y, -dirs[dir][0], -dirs[dir][1], 0) // check win in -ve dir
            ) >= 4) {
            return Win; // win
        }
    }
    return No_Win; // no win
}

uint8_t check_win(enum players **board, const uint8_t board_rows, const uint8_t board_cols, const int8_t x, const int8_t y, const int8_t dir_x, const int8_t dir_y, uint8_t inarow) {
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

