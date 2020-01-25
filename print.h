#ifndef PRINT_H
#define PRINR_H

#include <ncurses.h>

void print_board (WINDOW *game_window);
void print_piece(WINDOW *game_window, int y, int x);
void print_pieces(WINDOW *game_window, int **board, const int BOARD_ROWS, const int BOARD_COLS);
void print_title(WINDOW *title_window);

#endif /* ifndef PRINT_H */
