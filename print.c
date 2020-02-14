#include "print.h"

#include <ncurses.h>

void print_board(WINDOW *game_window) {
    int max_x, max_y;

    getmaxyx(game_window, max_y, max_x);

    mvwprintw(game_window, 1, 5, "1    2    3    4    5    6    7");
    wattron(game_window, COLOR_PAIR(Board));
    for ( int y = 2; y < max_y - 1; y++ ) {
        for ( int x = 2; x < max_x - 2; x++ ) {
            mvwaddch(game_window, y, x, ACS_BLOCK);
        }
    }
    wattroff(game_window, COLOR_PAIR(3));
    box(game_window, 0, 0);
    wrefresh(game_window);
}

void print_pieces(WINDOW *game_window, int **board, const int board_rows, const int board_cols, const int width_p_col, const int height_p_row) {
    // Loop through board and print prieces.
    int x, y;
    const int piece_offset_x = 4;
    const int piece_offset_y = 17;

    for (y=0; y<board_rows; y++) {
        for (x=0; x<board_cols; x++) {
            // Select colour based on value in board[y][x]
            wattron(game_window, COLOR_PAIR(board[y][x]));
            int print_x = (width_p_col * x) + piece_offset_x;
            int print_y = (height_p_row * -y) + piece_offset_y;
            mvwaddch(game_window, print_y, print_x, ACS_BLOCK); waddch(game_window, ACS_BLOCK);
            wattroff(game_window, COLOR_PAIR(board[y][x]));
        }
    }
    wmove(game_window, 0, 0);
    wrefresh(game_window);
}

void print_title(WINDOW *title_window) {
    //print title into title window
    mvwprintw(title_window, 1, 0,
            "| || | (_)_ __   __ _ _ __ _____      _\n"
            "| || |_| | '_ \\ / _` | '__/ _ \\ \\ /\\ / \n"
            "|__   _| | | | | (_| | | | (_) \\ V  V /\n"
            "   |_| |_|_| |_|\\__,_|_|  \\___/ \\_/\\_/");
    box(title_window, 0, 0);
    wrefresh(title_window);
}

