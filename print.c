#include "print.h"

#include <ncurses.h>

void print_board(WINDOW *game_window) {
    int x, y;

    mvwprintw(game_window, 1, 5, "1    2    3    4    5    6    7");
    for ( y=2; y<20; y++ ) {
        for ( x=2; x<38; x++ ) {
            wattron(game_window, COLOR_PAIR(3));
            mvwaddch(game_window, y, x, ACS_BLOCK);
            wattroff(game_window, COLOR_PAIR(3));
        }
    }
    box(game_window, 0, 0);
    wrefresh(game_window);
}

void print_pieces(WINDOW *game_window, int **board, const int BOARD_ROWS, const int BOARD_COLS) {
    int x, y;

    for (y=0; y<BOARD_ROWS; y++) {
        for (x=0; x<BOARD_COLS; x++) {
            wattron(game_window, COLOR_PAIR(board[y][x]));
            print_piece(game_window, x, y);
            wattroff(game_window, COLOR_PAIR(board[y][x]));
        }
    }
    wmove(game_window, 0, 0);
    wrefresh(game_window);
}

void print_piece(WINDOW *game_window, int x, int y) {
    int print_x = (5 * x) + 4;
    int print_y = (2 * -y) + 17;
    mvwaddch(game_window, print_y, print_x, ACS_BLOCK); waddch(game_window, ACS_BLOCK);
}

void print_title(WINDOW *title_window) {
    mvwprintw(title_window, 0, 0, " _  _   _\n| || | (_)_ __   __ _ _ __ _____      _\n| || |_| | '_ \\ / _` | '__/ _ \\ \\ /\\ / \n|__   _| | | | | (_| | | | (_) \\ V  V /\n   |_| |_|_| |_|\\__,_|_|  \\___/ \\_/\\_/");
    box(title_window, 0, 0);
    wrefresh(title_window);
}

