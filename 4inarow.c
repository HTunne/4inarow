#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#define BOARD_ROWS 8
#define BOARD_COLS 7

//int check_win(int board[8][7], int x, int y, int dir_x, int dir_x, int inarow);
//int check_all_wins(int board[8][7], int x, int y);
//void print_board (int board[8][7], char type[3]);
//int player_move(int board[8][7], int player, int x);
//int move_loop(int board[8][7], char type[3], int player);


int check_win(int board[BOARD_ROWS][BOARD_COLS], int x, int y, int dir_x, int dir_y, int inarow) {
    if ( inarow == 4 ) {
        return 1;
    } else if ( board[y][x] == 0 ) {
        return 0;
    } else if ( x + dir_x < 0 || x + dir_x > (BOARD_COLS-1) ) {
        return 0;
    } else if ( y + dir_y < 0 || y + dir_y > (BOARD_ROWS-1) ) {
        return 0;
    } else if ( board[y][x] != board[y+dir_y][x+dir_x] ) {
        return 0;
    } else {
        check_win(board, x+dir_x, y+dir_y, dir_x, dir_y, inarow + 1);
    }
}

int check_all_wins(int board[BOARD_ROWS][BOARD_COLS], int x, int y) {
    int dir_x, dir_y;

    for (dir_x=-1; dir_x<2; dir_x++)
        for (dir_y=-1; dir_y<2; dir_y++) {
            if ( !(dir_x==0 && dir_y==0) )
                if (check_win(board, x, y, dir_x, dir_y, 1))
                    return 1;
        }
    return 0;
}

void print_board (int board[BOARD_ROWS][BOARD_COLS], char type[3]) {
    int i, j;
    clear();
    for (i=0; i<BOARD_ROWS; i++) {
        printw(" ");
        refresh();
        for (j=0; j<BOARD_COLS; j++) {
            //printw("%i,%i", i, j);
            printw("|%c", type[board[BOARD_COLS-i][j]]);
            refresh();
            }
        printw("|\n");
        refresh();
    }
    printw("/^0^1^2^3^4^5^6^\\\n");
    refresh();

}

int player_move(int board[BOARD_ROWS][BOARD_COLS], int player, int x) {
    int y;
    for (y=0; y<BOARD_ROWS; y++) {
        if (board[y][x] == 0) {
            board[y][x] = player;
            return y;
        }
    }
    return -1;
}

int move_loop(int board[BOARD_ROWS][BOARD_COLS], char type[3], int player) {
    int valid_move = 0;
    int x, y;
    while ( !valid_move ) {
        printw("%c's move\nChoose column: ", type[player]);
        refresh();
        x = getch() - '0';
        //while ((getch()) != '\n');
        printw("\n");
        refresh();
        if ( x >= 0 && x < BOARD_COLS ) {
            y = player_move(board, player, x);
            if ( y > -1 )
                valid_move = 1;
        } else {
            printw("Invalid move, select again...");
            refresh();
        }
    }
    return check_all_wins(board, x, y);
}

int main() {
    initscr();
    noecho();
    cbreak();

    int board[BOARD_ROWS][BOARD_COLS] = {
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0}
    };
    char type[3] = " OX";
    int win_condition = 0;
    int player = 2;
    //game loop
    print_board(board, type);
    while ( !win_condition ) {
        if ( player == 1 ) {
            player = 2;
        } else {
            player = 1;
        }
        win_condition = move_loop(board, type, player);
        print_board(board, type);
    }
    printw("%c wins!!\n", type[player]);
    refresh();
    return 0;
}

