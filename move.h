#ifndef MOVE_H
#define MOVE_H value

#include <ncurses.h>
enum win_conditions{No_Win, Win, Draw, Reset};
enum win_conditions move_loop(WINDOW *dialogue_window, int **board, const int board_rows, const int board_cols, const int player);
int player_move(int **board, const int board_rows, const int player, const int x);
enum win_conditions check_all_wins(int **board, const int board_rows, const int board_cols, const int x, const int y);
int check_win(int **board, const int board_rows, const int board_cols, const int x, const int y, const int dir_x, const int dir_y, int inarow);

#endif /* ifndef MOVE_H */
