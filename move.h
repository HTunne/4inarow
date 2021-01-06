#pragma once

#include <ncurses.h>
#include "print.h"

enum win_conditions{No_Win, Win, Draw, Reset};
enum win_conditions move_loop(WINDOW *dialogue_window, enum players **board, const uint8_t board_rows, const uint8_t board_cols, const enum players player);
bool is_draw(enum players **board, const uint8_t board_rows, const uint8_t board_cols);
int8_t player_move(enum players **board, const uint8_t board_rows, const enum players player, const uint8_t x);
enum win_conditions check_all_wins(enum players **board, const uint8_t board_rows, const uint8_t board_cols, const uint8_t x, const uint8_t y);
uint8_t check_win(enum players **board, const uint8_t board_rows, const uint8_t board_cols, const int8_t x, const int8_t y, const int8_t dir_x, const int8_t dir_y, uint8_t inarow);
