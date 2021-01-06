#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ncurses.h>

#include "print.h"
#include "move.h"
#include "dialogue.h"

void init_board(enum players **board, uint8_t board_rows, uint8_t board_cols);

int main() {

    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    const uint8_t board_rows = 8;
    const uint8_t board_cols = 7;

    // Allocate board as an array of pointers to arrays
    enum players **board = (enum players **)malloc(board_rows * sizeof(enum players *));
    for (uint8_t row = 0; row < board_rows; row++)
        board[row] = (enum players *)malloc(board_cols * sizeof(enum players));

    init_pair(Blank, COLOR_BLACK, COLOR_BLACK);
    init_pair(Player_1, COLOR_YELLOW, COLOR_BLACK);    // Piece colour for player 1
    init_pair(Player_2, COLOR_RED, COLOR_BLACK);       // Piece colour for player 2
    init_pair(Board, COLOR_BLUE, COLOR_BLACK);

    // Geometry for window sizes
    const uint8_t game_window_h_offset = 4;
    const uint8_t window_w_offset = 5;
    const uint8_t title_window_height = 6;
    const uint8_t dialogue_window_height = 6;
    const uint8_t width_p_col = 5;
    const uint8_t height_p_row = 2;

    uint8_t game_window_height = (height_p_row * board_rows) + game_window_h_offset;
    uint8_t window_width = (width_p_col * board_cols) + window_w_offset;
    uint8_t start_y = (LINES - (title_window_height + game_window_height + dialogue_window_height)) / 2;
	uint8_t start_x = (COLS - window_width) / 2;

    WINDOW *title_window;
    WINDOW *game_window;
    WINDOW *dialogue_window;

    title_window = newwin(title_window_height, window_width, start_y, start_x);
    game_window = newwin(game_window_height, window_width, start_y + title_window_height, start_x);
    dialogue_window = newwin(dialogue_window_height, window_width, start_y + title_window_height + game_window_height, start_x);

    print_title(title_window);

    print_board(game_window);

    bool play_again = true;

    //game loop
    while (play_again) {

        // setup a new game
        enum players player = Player_2; // start on player 2 as player will flip before first move
        enum win_conditions win_condition = No_Win;
        init_board(board, board_rows, board_cols);
        print_pieces(game_window, board, board_rows, board_cols, width_p_col, height_p_row);

        while (win_condition == No_Win) {
            if (player == Player_1) {
                player = Player_2;
            } else {
                player = Player_1;
            }
            move_dialog(dialogue_window, player);
            win_condition = move_loop(dialogue_window, board, board_rows, board_cols, player);
            print_pieces(game_window, board, board_rows, board_cols, width_p_col, height_p_row);
        }

        if (win_condition != Reset) {
            play_again = play_again_dialogue(dialogue_window, player, win_condition);
        }

    }

    endwin();
    return 0;
}

void init_board(enum players **board, uint8_t board_rows, uint8_t board_cols) {
    for (uint8_t row = 0; row < board_rows; row++) {
        for (uint8_t col = 0; col < board_cols; col++) {
            board[row][col] = Blank;
        }
    }
}

