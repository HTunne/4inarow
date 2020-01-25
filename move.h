#ifndef MOVE_H
#define MOVE_H value

#include <ncurses.h>

int move_loop(WINDOW *dialogue_window, int **board, const int BOARD_ROWS, const int BOARD_COLS, int player);
int player_move(int **board, const int BOARD_ROWS, int player, int x);
int check_all_wins(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y);
int check_win(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y, int dir_x, int dir_y, int inarow);

#endif /* ifndef MOVE_H */
