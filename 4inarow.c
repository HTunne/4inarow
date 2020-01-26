#include <stdlib.h>
#include <ncurses.h>

#include "print.h"
#include "move.h"
#include "dialogue.h"

void init_board(int **board, int BOARD_ROWS, int BOARD_COLS);

int main() {

    const int BOARD_ROWS = 8;
    const int BOARD_COLS = 7;
    const int game_window_h_offset = 4;
    const int window_w_offset = 5;
    const int title_window_height = 6;
    const int dialogue_window_height = 6;

    int start_x, start_y, window_width, game_window_height;
    enum win_conditions win_condition = No_Win;
    int play_again = 1;
    int player = 2; // start on player 2 as player will flip before first move

    // Allocate board as an array of pointers to arrays
    int **board = (int **)malloc(BOARD_ROWS * sizeof(int *));
    for (int row = 0; row < BOARD_ROWS; row++)
        board[row] = (int *)malloc(BOARD_COLS * sizeof(int));

    WINDOW *title_window;
    WINDOW *game_window;
    WINDOW *dialogue_window;

    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    game_window_height = (2 * BOARD_ROWS) + game_window_h_offset;
    window_width = (5 * BOARD_COLS) + window_w_offset;
    start_y = (LINES - (title_window_height + game_window_height + dialogue_window_height)) / 2;
	start_x = (COLS - window_width) / 2;

    title_window = newwin(title_window_height, window_width, start_y, start_x);
    game_window = newwin(game_window_height, window_width, start_y + title_window_height, start_x);
    dialogue_window = newwin(dialogue_window_height, window_width, start_y + title_window_height + game_window_height, start_x);

    print_title(title_window);

    print_board(game_window);

    while (play_again) {
        //game loop
        init_board(board, BOARD_ROWS, BOARD_COLS);
        print_pieces(game_window, board, BOARD_ROWS, BOARD_COLS);

        win_condition = No_Win;

        while ( win_condition == No_Win ) {
            if ( player == 1 ) {
                player = 2;
            } else {
                player = 1;
            }
            move_dialog(dialogue_window, player);
            win_condition = move_loop(dialogue_window, board, BOARD_ROWS, BOARD_COLS, player);
            print_pieces(game_window, board, BOARD_ROWS, BOARD_COLS);
        }

        if (win_condition == Reset) {
            play_again = 1;
        } else {
            play_again = play_again_dialogue(dialogue_window, player, win_condition);
        }

    }


    endwin();
    return 0;
}

void init_board(int **board, int BOARD_ROWS, int BOARD_COLS) {
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            board[row][col] = 0;
        }
    }
}

