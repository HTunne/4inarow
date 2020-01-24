#include "4inarow.h"


void init_board(int **board, int BOARD_ROWS, int BOARD_COLS);
void print_board (WINDOW *game_window);
void print_piece(WINDOW *game_window, int y, int x);
void print_pieces(WINDOW *game_window, int **board, const int BOARD_ROWS, const int BOARD_COLS);
int move_loop(WINDOW *text_window, int **board, const int BOARD_ROWS, const int BOARD_COLS, int player);
int player_move(int **board, const int BOARD_ROWS, int player, int x);
int check_all_wins(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y);
int check_win(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y, int dir_x, int dir_y, int inarow);

int main() {
    const int BOARD_ROWS = 8;
    const int BOARD_COLS = 7;

    WINDOW *game_window;
    WINDOW *text_window;

    int start_x, start_y, width, height;
    int win_condition = 0;
    int player = 2;

    int **board = (int **)malloc(BOARD_ROWS * sizeof(int *));
    for (int row = 0; row < BOARD_ROWS; row++)
        board[row] = (int *)malloc(BOARD_COLS * sizeof(int));

    init_board(board, BOARD_ROWS, BOARD_COLS);

    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    height = (2 * BOARD_ROWS) + 3;
    width = (5 * BOARD_COLS) + 5;
    start_y = 24;
	start_x = 0;

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    game_window = newwin(height, width, start_y, start_x);
    text_window = newwin(6, width, start_y + height, start_x);

    box(text_window, 0, 0);
    wrefresh(text_window);

    box(game_window, 0, 0);
    wrefresh(game_window);

    //game loop
    print_board(game_window);
    print_pieces(game_window, board, BOARD_ROWS, BOARD_COLS);
    while ( !win_condition ) {
        if ( player == 1 ) {
            player = 2;
        } else {
            player = 1;
        }
        win_condition = move_loop(text_window, board, BOARD_ROWS, BOARD_COLS, player);
        print_pieces(game_window, board, BOARD_ROWS, BOARD_COLS);
    }

    wclear(text_window);
    wattron(text_window, COLOR_PAIR(player));
    mvwaddch(text_window, 2, 3, ACS_BLOCK);
    waddch(text_window, ACS_BLOCK);
    wattroff(text_window, COLOR_PAIR(player));
    wprintw(text_window, " wins!!\n");
    box(text_window, 0, 0);
    wrefresh(text_window);

    while ( 1 ) {
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

void print_board(WINDOW *game_window) {
    int x, y;

    for ( y=0; y<18; y++ ) {
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
    int print_y = (2 * -y) + 16;
    mvwaddch(game_window, print_y, print_x, ACS_BLOCK); waddch(game_window, ACS_BLOCK);
}

int move_loop(WINDOW *text_window, int **board, const int BOARD_ROWS, const int BOARD_COLS, int player) {
    int valid_move = 0;
    int x, y;

    while ( !valid_move ) {
        wclear(text_window);
        wattron(text_window, COLOR_PAIR(player));
        mvwaddch(text_window, 2, 3, ACS_BLOCK);
        waddch(text_window, ACS_BLOCK);
        wattroff(text_window, COLOR_PAIR(player));
        wprintw(text_window, "'s move.!!");
        mvwprintw(text_window, 3, 3, "Choose column...");
        box(text_window, 0, 0);
        wrefresh(text_window);

        x = wgetch(text_window) - '0';
        if ( x >= 0 && x < BOARD_COLS ) {
            y = player_move(board, BOARD_ROWS, player, x);
            if ( y > -1 )
                valid_move = 1;
        }
    }
    return check_all_wins(board, BOARD_ROWS, BOARD_COLS, x, y);
}

int player_move(int **board, const int BOARD_ROWS, int player, int x) {
    int y;

    for (y = 0; y < BOARD_ROWS; y++) {
        if (board[y][x] == 0) {
            board[y][x] = player;
            return y;
        }
    }
    return -1;
}

int check_all_wins(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y) {
    int dir_x, dir_y;

    for (dir_x=-1; dir_x<2; dir_x++)
        for (dir_y=-1; dir_y<2; dir_y++) {
            if ( !(dir_x==0 && dir_y==0) )
                if (check_win(board, BOARD_ROWS, BOARD_COLS, x, y, dir_x, dir_y, 1))
                    return 1;
        }
    return 0;
}

int check_win(int **board, const int BOARD_ROWS, const int BOARD_COLS, int x, int y, int dir_x, int dir_y, int inarow) {
    // Recusively crawls from (x, y) in direction (dir_x, dir_y) until...
    if ( inarow == 4 ) { // 4 in a row found, win!
        return 1;
    } else if (
            x + dir_x < 0 ||                // hits left side of board, no win
            x + dir_x > (BOARD_COLS-1) ||   // hits right side of board, no win
            y + dir_y < 0 ||                // hits bottom of board, no win
            y + dir_y > (BOARD_ROWS-1)      // hits top of board, no win
            ) {
        return 0;
    } else if ( board[y][x] != board[y+dir_y][x+dir_x] ) { // hits empty or opposing players square, no win
        return 0;
    } else {
        check_win(board, BOARD_ROWS, BOARD_COLS, x+dir_x, y+dir_y, dir_x, dir_y, inarow + 1); // check next square and increment inarow counter
    }
}

