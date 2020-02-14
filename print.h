#pragma once

#include <ncurses.h>

enum players{Blank, Player_1, Player_2, Board};
void print_board (WINDOW *game_window);
void print_pieces(WINDOW *game_window, int **board, const int board_rows, const int board_cols, const int width_p_col, const int height_p_row);
void print_title(WINDOW *title_window);

