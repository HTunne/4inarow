#ifndef PRINT_H
#define PRINR_H

#include <ncurses.h>

void print_board (WINDOW *game_window);
void print_pieces(WINDOW *game_window, int **board, const int board_rows, const int board_cols, const int width_p_col, const int height_p_row);
void print_title(WINDOW *title_window);

#endif /* ifndef PRINT_H */
