#ifndef _4INAROW_
#define _4INAROW_

#include <ncurses.h>
#include <stdio.h>
#include <string.h>

void init_board(int **board, int BOARD_ROWS, int BOARD_COLS);
void print_board (WINDOW *game_window);
void print_piece(WINDOW *game_window, int y, int x);
void print_pieces(WINDOW *game_window, int **board, const int BOARD_ROWS, const int BOARD_COLS);
int move_loop(WINDOW *text_window, int **board, const int BOARD_ROWS, const int BOARD_COLS, int player);
int player_move(int **board, const int BOARD_ROWS, int player, int x);
int check_all_wins(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y);
int check_win(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y, int dir_x, int dir_y, int inarow);

#endif /* ifndef _4INAROW_ */
